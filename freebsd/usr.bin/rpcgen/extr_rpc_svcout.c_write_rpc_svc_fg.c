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
 int /*<<< orphan*/  f_print (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  fout ; 
 scalar_t__ inetdflag ; 
 scalar_t__ logflag ; 
 int /*<<< orphan*/  open_log_file (char const*,char const*) ; 
 scalar_t__ tirpcflag ; 

__attribute__((used)) static void
write_rpc_svc_fg(const char *infile, const char *sp)
{
	f_print(fout, "#ifndef RPC_SVC_FG\n");
	f_print(fout, "%sint size;\n", sp);
	if (tirpcflag)
		f_print(fout, "%sstruct rlimit rl;\n", sp);
	if (inetdflag)
		f_print(fout, "%sint pid, i;\n\n", sp);
	f_print(fout, "%spid = fork();\n", sp);
	f_print(fout, "%sif (pid < 0) {\n", sp);
	f_print(fout, "%s\tperror(\"cannot fork\");\n", sp);
	f_print(fout, "%s\texit(1);\n", sp);
	f_print(fout, "%s}\n", sp);
	f_print(fout, "%sif (pid)\n", sp);
	f_print(fout, "%s\texit(0);\n", sp);
	/* get number of file descriptors */
	if (tirpcflag) {
		f_print(fout, "%srl.rlim_max = 0;\n", sp);
		f_print(fout, "%sif (getrlimit(RLIMIT_NOFILE, &rl) == -1) {\n",
		    sp);
		f_print(fout, "%s\tperror(\"getrlimit\");\n", sp);
		f_print(fout, "%s\texit(1);\n", sp);
		f_print(fout, "%s}\n", sp);
		f_print(fout, "%sif ((size = rl.rlim_max) == 0)\n", sp);
		f_print(fout, "%s\texit(1);\n", sp);
	} else {
		f_print(fout, "%ssize = getdtablesize();\n", sp);
	}

	f_print(fout, "%sfor (i = 0; i < size; i++)\n", sp);
	f_print(fout, "%s\t(void) close(i);\n", sp);
	/* Redirect stderr and stdout to console */
	f_print(fout, "%si = open(\"/dev/console\", 2);\n", sp);
	f_print(fout, "%s(void) dup2(i, 1);\n", sp);
	f_print(fout, "%s(void) dup2(i, 2);\n", sp);
	/* This removes control of the controlling terminal */
	if (tirpcflag)
		f_print(fout, "%ssetsid();\n", sp);
	else {
		f_print(fout, "%si = open(\"/dev/tty\", 2);\n", sp);
		f_print(fout, "%sif (i >= 0) {\n", sp);
		f_print(fout,
			"%s\t(void) ioctl(i, TIOCNOTTY, (char *)NULL);\n", sp);
		f_print(fout, "%s\t(void) close(i);\n", sp);
		f_print(fout, "%s}\n", sp);
	}
	if (!logflag)
		open_log_file(infile, sp);
	f_print(fout, "#endif\n");
	if (logflag)
		open_log_file(infile, sp);
}