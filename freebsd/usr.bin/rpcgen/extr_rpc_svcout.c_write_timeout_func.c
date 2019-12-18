#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 int /*<<< orphan*/  f_print (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  fout ; 
 scalar_t__ mtflag ; 
 scalar_t__ pmflag ; 
 int /*<<< orphan*/  timerflag ; 
 scalar_t__ tirpcflag ; 

__attribute__((used)) static void
write_timeout_func(void)
{
	if (!timerflag)
		return;

	f_print(fout, "\n");
	f_print(fout, "static void\n");
	f_print(fout, "closedown(int sig)\n");
	f_print(fout, "{\n");
	if (mtflag)
		f_print(fout, "\tpthread_mutex_lock(&_svcstate_lock);\n");
	f_print(fout, "\tif (_rpcsvcstate == _IDLE) {\n");
	f_print(fout, "\t\textern fd_set svc_fdset;\n");
	f_print(fout, "\t\tstatic int size;\n");
	f_print(fout, "\t\tint i, openfd;\n");
	if (tirpcflag && pmflag) {
		f_print(fout, "\t\tstruct t_info tinfo;\n\n");
		f_print(fout,
			"\t\tif (!t_getinfo(0, &tinfo) && (tinfo.servtype == T_CLTS))\n");
	} else {
		f_print(fout, "\n\t\tif (_rpcfdtype == SOCK_DGRAM)\n");
	}
	f_print(fout, "\t\t\texit(0);\n");
	f_print(fout, "\t\tif (size == 0) {\n");
	if (tirpcflag) {
		f_print(fout, "\t\t\tstruct rlimit rl;\n\n");
		f_print(fout, "\t\t\trl.rlim_max = 0;\n");
		f_print(fout, "\t\t\tif (getrlimit(RLIMIT_NOFILE, &rl) == -1)\n");
		f_print(fout, "\t\t\t\treturn;\n");
		f_print(fout, "\t\t\tif ((size = rl.rlim_max) == 0) {\n");
		
		if (mtflag)
			f_print(fout, "\t\t\t\tpthread_mutex_unlock(&_svcstate_lock);\n");

		f_print(fout, "\t\t\t\treturn;\n\t\t\t}\n");
	} else {
		f_print(fout, "\t\t\tsize = getdtablesize();\n");
	}
	f_print(fout, "\t\t}\n");
	f_print(fout,
		"\t\tfor (i = 0, openfd = 0; i < size && openfd < 2; i++)\n");
	f_print(fout, "\t\t\tif (FD_ISSET(i, &svc_fdset))\n");
	f_print(fout, "\t\t\t\topenfd++;\n");
	f_print(fout, "\t\tif (openfd <= 1)\n");
	f_print(fout, "\t\t\texit(0);\n");
	f_print(fout, "\t}\n");
	f_print(fout, "\tif (_rpcsvcstate == _SERVED)\n");
	f_print(fout, "\t\t_rpcsvcstate = _IDLE;\n\n");
	if (mtflag)
		f_print(fout, "\tpthread_mutex_unlock(&_svcstate_lock);\n");

	f_print(fout, "\t(void) signal(SIGALRM, closedown);\n");
	f_print(fout, "\t(void) alarm(_RPCSVC_CLOSEDOWN/2);\n");
	f_print(fout, "}\n");

}