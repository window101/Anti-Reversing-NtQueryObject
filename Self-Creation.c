
#include windows.h
#include tchar.h
#include stdio.h

void ChildProc() {
  MessageBox(NULL, L"This is a child process!", L"DebugMe2", MB_OK);
  ExitProcess(0);
}
void _tmain(int argc, TCHAR *argv[]) {
  
  TCHAR szPath[MAX_PATH] = {0, };
  STARTUPINFO si = {sizeof(STARTUPINFO), };
  PROCESS_INFORMATION pi = {0,};
  CONTEXT ctx = {0,};
  
  _tprintf(L"This is a parent process\n");
  GetMoudleFileName(NULL, szPath, sizeof(TCHAR) * MAX_PATH);
  
  CreateProcess(szPath, NULL, NULL, NULL, FALSE,
                CREATE_SUSPENDED,
                NULL, NULL, &si, &pi);
  ctx.ContextFlags = CONTEXT_FULL;
  
  GetThreadContext(pi.hThread, &ctx);
  ctx.Eip = (DWORD)ChildProc;
  
  SetThreadContext(pi.hThread, &ctx);
  
  ResumeThread(pi.hThread);
  
  WaitForSingleObject(pi.hProcess, INFINITE);
  
  CloseHandle(pi.hProcess);
  CloseHandle(pi.hThread);
}
