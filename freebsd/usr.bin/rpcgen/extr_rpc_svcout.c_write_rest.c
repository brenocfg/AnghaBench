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
 int /*<<< orphan*/  TRANSP ; 
 int /*<<< orphan*/  _errbuf ; 
 int /*<<< orphan*/  f_print (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  fout ; 
 scalar_t__ inetdflag ; 
 int /*<<< orphan*/  print_err_message (char*) ; 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ timerflag ; 

void
write_rest(void)
{
	f_print(fout, "\n");
	if (inetdflag) {
		f_print(fout, "\tif (%s == (SVCXPRT *)NULL) {\n", TRANSP);
		(void) sprintf(_errbuf, "could not create a handle");
		print_err_message("\t\t");
		f_print(fout, "\t\texit(1);\n");
		f_print(fout, "\t}\n");
		if (timerflag) {
			f_print(fout, "\tif (_rpcpmstart) {\n");
			f_print(fout,
				"\t\t(void) signal(SIGALRM, closedown);\n");
			f_print(fout, "\t\t(void) \
alarm(_RPCSVC_CLOSEDOWN/2);\n");
			f_print(fout, "\t}\n");
		}
	}
	f_print(fout, "\tsvc_run();\n");
	(void) sprintf(_errbuf, "svc_run returned");
	print_err_message("\t");
	f_print(fout, "\texit(1);\n");
	f_print(fout, "\t/* NOTREACHED */\n");
	f_print(fout, "}\n");
}