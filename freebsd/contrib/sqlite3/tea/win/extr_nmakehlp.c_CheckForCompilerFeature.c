#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  msg ;
struct TYPE_12__ {int /*<<< orphan*/  buffer; int /*<<< orphan*/  pipe; } ;
struct TYPE_11__ {int cb; int nLength; int /*<<< orphan*/  hProcess; int /*<<< orphan*/  hThread; int /*<<< orphan*/  hStdError; int /*<<< orphan*/  hStdOutput; int /*<<< orphan*/  bInheritHandle; int /*<<< orphan*/ * lpSecurityDescriptor; int /*<<< orphan*/  hStdInput; int /*<<< orphan*/  dwFlags; } ;
typedef  TYPE_1__ STARTUPINFO ;
typedef  TYPE_1__ SECURITY_ATTRIBUTES ;
typedef  TYPE_1__ PROCESS_INFORMATION ;
typedef  int /*<<< orphan*/  LPVOID ;
typedef  int /*<<< orphan*/  HANDLE ;
typedef  int DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CloseHandle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CreatePipe (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CreateProcess (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  CreateThread (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_5__*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  DETACHED_PROCESS ; 
 int DUPLICATE_CLOSE_SOURCE ; 
 int DUPLICATE_SAME_ACCESS ; 
 int /*<<< orphan*/  DuplicateHandle (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 TYPE_5__ Err ; 
 int /*<<< orphan*/  FALSE ; 
 int FORMAT_MESSAGE_FROM_SYSTEM ; 
 int FORMAT_MESSAGE_IGNORE_INSERTS ; 
 int FORMAT_MESSAGE_MAX_WIDTH_MASK ; 
 int /*<<< orphan*/  FormatMessage (int,long,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetCurrentProcess () ; 
 int GetLastError () ; 
 int /*<<< orphan*/  GetStdHandle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INFINITE ; 
 int /*<<< orphan*/  INVALID_HANDLE_VALUE ; 
 TYPE_5__ Out ; 
 int /*<<< orphan*/  ReadFromPipe ; 
 int /*<<< orphan*/  STARTF_USESTDHANDLES ; 
 int /*<<< orphan*/  STD_ERROR_HANDLE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  WaitForInputIdle (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  WaitForMultipleObjects (int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  WaitForSingleObject (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WriteFile (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ZeroMemory (TYPE_1__*,int) ; 
 int /*<<< orphan*/  lstrcat (char*,char const*) ; 
 int /*<<< orphan*/  lstrcpy (char*,char*) ; 
 int /*<<< orphan*/  lstrlen (char*) ; 
 int snprintf (char*,int,char*,char*,int) ; 
 int /*<<< orphan*/ * strstr (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int
CheckForCompilerFeature(
    const char *option)
{
    STARTUPINFO si;
    PROCESS_INFORMATION pi;
    SECURITY_ATTRIBUTES sa;
    DWORD threadID;
    char msg[300];
    BOOL ok;
    HANDLE hProcess, h, pipeThreads[2];
    char cmdline[100];

    hProcess = GetCurrentProcess();

    ZeroMemory(&pi, sizeof(PROCESS_INFORMATION));
    ZeroMemory(&si, sizeof(STARTUPINFO));
    si.cb = sizeof(STARTUPINFO);
    si.dwFlags   = STARTF_USESTDHANDLES;
    si.hStdInput = INVALID_HANDLE_VALUE;

    ZeroMemory(&sa, sizeof(SECURITY_ATTRIBUTES));
    sa.nLength = sizeof(SECURITY_ATTRIBUTES);
    sa.lpSecurityDescriptor = NULL;
    sa.bInheritHandle = FALSE;

    /*
     * Create a non-inheritible pipe.
     */

    CreatePipe(&Out.pipe, &h, &sa, 0);

    /*
     * Dupe the write side, make it inheritible, and close the original.
     */

    DuplicateHandle(hProcess, h, hProcess, &si.hStdOutput, 0, TRUE,
	    DUPLICATE_SAME_ACCESS | DUPLICATE_CLOSE_SOURCE);

    /*
     * Same as above, but for the error side.
     */

    CreatePipe(&Err.pipe, &h, &sa, 0);
    DuplicateHandle(hProcess, h, hProcess, &si.hStdError, 0, TRUE,
	    DUPLICATE_SAME_ACCESS | DUPLICATE_CLOSE_SOURCE);

    /*
     * Base command line.
     */

    lstrcpy(cmdline, "cl.exe -nologo -c -TC -Zs -X -Fp.\\_junk.pch ");

    /*
     * Append our option for testing
     */

    lstrcat(cmdline, option);

    /*
     * Filename to compile, which exists, but is nothing and empty.
     */

    lstrcat(cmdline, " .\\nul");

    ok = CreateProcess(
	    NULL,	    /* Module name. */
	    cmdline,	    /* Command line. */
	    NULL,	    /* Process handle not inheritable. */
	    NULL,	    /* Thread handle not inheritable. */
	    TRUE,	    /* yes, inherit handles. */
	    DETACHED_PROCESS, /* No console for you. */
	    NULL,	    /* Use parent's environment block. */
	    NULL,	    /* Use parent's starting directory. */
	    &si,	    /* Pointer to STARTUPINFO structure. */
	    &pi);	    /* Pointer to PROCESS_INFORMATION structure. */

    if (!ok) {
	DWORD err = GetLastError();
	int chars = snprintf(msg, sizeof(msg) - 1,
		"Tried to launch: \"%s\", but got error [%u]: ", cmdline, err);

	FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM|FORMAT_MESSAGE_IGNORE_INSERTS|
		FORMAT_MESSAGE_MAX_WIDTH_MASK, 0L, err, 0, (LPVOID)&msg[chars],
		(300-chars), 0);
	WriteFile(GetStdHandle(STD_ERROR_HANDLE), msg, lstrlen(msg), &err,NULL);
	return 2;
    }

    /*
     * Close our references to the write handles that have now been inherited.
     */

    CloseHandle(si.hStdOutput);
    CloseHandle(si.hStdError);

    WaitForInputIdle(pi.hProcess, 5000);
    CloseHandle(pi.hThread);

    /*
     * Start the pipe reader threads.
     */

    pipeThreads[0] = CreateThread(NULL, 0, ReadFromPipe, &Out, 0, &threadID);
    pipeThreads[1] = CreateThread(NULL, 0, ReadFromPipe, &Err, 0, &threadID);

    /*
     * Block waiting for the process to end.
     */

    WaitForSingleObject(pi.hProcess, INFINITE);
    CloseHandle(pi.hProcess);

    /*
     * Wait for our pipe to get done reading, should it be a little slow.
     */

    WaitForMultipleObjects(2, pipeThreads, TRUE, 500);
    CloseHandle(pipeThreads[0]);
    CloseHandle(pipeThreads[1]);

    /*
     * Look for the commandline warning code in both streams.
     *  - in MSVC 6 & 7 we get D4002, in MSVC 8 we get D9002.
     */

    return !(strstr(Out.buffer, "D4002") != NULL
             || strstr(Err.buffer, "D4002") != NULL
             || strstr(Out.buffer, "D9002") != NULL
             || strstr(Err.buffer, "D9002") != NULL
             || strstr(Out.buffer, "D2021") != NULL
             || strstr(Err.buffer, "D2021") != NULL);
}