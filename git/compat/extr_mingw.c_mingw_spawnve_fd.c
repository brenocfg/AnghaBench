#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  char wchar_t ;
struct strbuf {int len; scalar_t__* buf; } ;
struct pinfo_t {struct pinfo_t* next; int /*<<< orphan*/  proc; int /*<<< orphan*/  pid; } ;
typedef  int /*<<< orphan*/  si ;
typedef  int pid_t ;
typedef  int /*<<< orphan*/  pi ;
struct TYPE_6__ {int cb; scalar_t__ hThread; int /*<<< orphan*/  dwProcessId; int /*<<< orphan*/  hProcess; void* hStdError; void* hStdOutput; void* hStdInput; int /*<<< orphan*/  dwFlags; } ;
typedef  TYPE_1__ STARTUPINFOW ;
typedef  TYPE_1__ PROCESS_INFORMATION ;
typedef  scalar_t__ HANDLE ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  ALLOC_ARRAY (char*,int /*<<< orphan*/ ) ; 
 unsigned int CREATE_UNICODE_ENVIRONMENT ; 
 int /*<<< orphan*/  CloseHandle (scalar_t__) ; 
 scalar_t__ CreateFileW (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CreateProcessW (char*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned int,char*,char*,TYPE_1__*,TYPE_1__*) ; 
 unsigned int DETACHED_PROCESS ; 
 int /*<<< orphan*/  ENOENT ; 
 int /*<<< orphan*/  EnterCriticalSection (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FILE_ATTRIBUTE_NORMAL ; 
 int /*<<< orphan*/  FILE_SHARE_WRITE ; 
 int /*<<< orphan*/  GENERIC_WRITE ; 
 scalar_t__ INVALID_HANDLE_VALUE ; 
 int /*<<< orphan*/  LeaveCriticalSection (int /*<<< orphan*/ *) ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  OPEN_EXISTING ; 
 int /*<<< orphan*/  STARTF_USESTDHANDLES ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  do_unset_environment_variables () ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ is_msys2_sh (char const*) ; 
 char* make_environment_block (char**) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 struct pinfo_t* pinfo ; 
 int /*<<< orphan*/  pinfo_cs ; 
 char const* quote_arg_msvc (char const*) ; 
 char const* quote_arg_msys2 (char const*) ; 
 int /*<<< orphan*/  st_add (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  st_mult (int,int) ; 
 int /*<<< orphan*/  strbuf_addch (struct strbuf*,char) ; 
 int /*<<< orphan*/  strbuf_addstr (struct strbuf*,char*) ; 
 int /*<<< orphan*/  strbuf_init (struct strbuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 int /*<<< orphan*/  strcmp (char const*,char const*) ; 
 void* winansi_get_osfhandle (int) ; 
 struct pinfo_t* xmalloc (int) ; 
 int /*<<< orphan*/  xutftowcs (char*,scalar_t__*,int) ; 
 scalar_t__ xutftowcs_path (char*,char const*) ; 

__attribute__((used)) static pid_t mingw_spawnve_fd(const char *cmd, const char **argv, char **deltaenv,
			      const char *dir,
			      int prepend_cmd, int fhin, int fhout, int fherr)
{
	STARTUPINFOW si;
	PROCESS_INFORMATION pi;
	struct strbuf args;
	wchar_t wcmd[MAX_PATH], wdir[MAX_PATH], *wargs, *wenvblk = NULL;
	unsigned flags = CREATE_UNICODE_ENVIRONMENT;
	BOOL ret;
	HANDLE cons;
	const char *(*quote_arg)(const char *arg) =
		is_msys2_sh(*argv) ? quote_arg_msys2 : quote_arg_msvc;

	do_unset_environment_variables();

	/* Determine whether or not we are associated to a console */
	cons = CreateFileW(L"CONOUT$", GENERIC_WRITE,
			FILE_SHARE_WRITE, NULL, OPEN_EXISTING,
			FILE_ATTRIBUTE_NORMAL, NULL);
	if (cons == INVALID_HANDLE_VALUE) {
		/* There is no console associated with this process.
		 * Since the child is a console process, Windows
		 * would normally create a console window. But
		 * since we'll be redirecting std streams, we do
		 * not need the console.
		 * It is necessary to use DETACHED_PROCESS
		 * instead of CREATE_NO_WINDOW to make ssh
		 * recognize that it has no console.
		 */
		flags |= DETACHED_PROCESS;
	} else {
		/* There is already a console. If we specified
		 * DETACHED_PROCESS here, too, Windows would
		 * disassociate the child from the console.
		 * The same is true for CREATE_NO_WINDOW.
		 * Go figure!
		 */
		CloseHandle(cons);
	}
	memset(&si, 0, sizeof(si));
	si.cb = sizeof(si);
	si.dwFlags = STARTF_USESTDHANDLES;
	si.hStdInput = winansi_get_osfhandle(fhin);
	si.hStdOutput = winansi_get_osfhandle(fhout);
	si.hStdError = winansi_get_osfhandle(fherr);

	if (*argv && !strcmp(cmd, *argv))
		wcmd[0] = L'\0';
	else if (xutftowcs_path(wcmd, cmd) < 0)
		return -1;
	if (dir && xutftowcs_path(wdir, dir) < 0)
		return -1;

	/* concatenate argv, quoting args as we go */
	strbuf_init(&args, 0);
	if (prepend_cmd) {
		char *quoted = (char *)quote_arg(cmd);
		strbuf_addstr(&args, quoted);
		if (quoted != cmd)
			free(quoted);
	}
	for (; *argv; argv++) {
		char *quoted = (char *)quote_arg(*argv);
		if (*args.buf)
			strbuf_addch(&args, ' ');
		strbuf_addstr(&args, quoted);
		if (quoted != *argv)
			free(quoted);
	}

	ALLOC_ARRAY(wargs, st_add(st_mult(2, args.len), 1));
	xutftowcs(wargs, args.buf, 2 * args.len + 1);
	strbuf_release(&args);

	wenvblk = make_environment_block(deltaenv);

	memset(&pi, 0, sizeof(pi));
	ret = CreateProcessW(*wcmd ? wcmd : NULL, wargs, NULL, NULL, TRUE,
		flags, wenvblk, dir ? wdir : NULL, &si, &pi);

	free(wenvblk);
	free(wargs);

	if (!ret) {
		errno = ENOENT;
		return -1;
	}
	CloseHandle(pi.hThread);

	/*
	 * The process ID is the human-readable identifier of the process
	 * that we want to present in log and error messages. The handle
	 * is not useful for this purpose. But we cannot close it, either,
	 * because it is not possible to turn a process ID into a process
	 * handle after the process terminated.
	 * Keep the handle in a list for waitpid.
	 */
	EnterCriticalSection(&pinfo_cs);
	{
		struct pinfo_t *info = xmalloc(sizeof(struct pinfo_t));
		info->pid = pi.dwProcessId;
		info->proc = pi.hProcess;
		info->next = pinfo;
		pinfo = info;
	}
	LeaveCriticalSection(&pinfo_cs);

	return (pid_t)pi.dwProcessId;
}