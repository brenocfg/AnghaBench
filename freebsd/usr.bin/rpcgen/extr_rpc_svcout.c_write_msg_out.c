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
 scalar_t__ inetdflag ; 
 scalar_t__ pmflag ; 

__attribute__((used)) static void
write_msg_out(void)
{
	f_print(fout, "\n");
/*
 * Avoid making _msgout() static -- it's useful to have it visible
 * in the toplevel RPC server code.
 */
	f_print(fout, "static\n");
	f_print(fout, "void _msgout(const char* msg)\n");
	f_print(fout, "{\n");
	f_print(fout, "#ifdef RPC_SVC_FG\n");
	if (inetdflag || pmflag)
		f_print(fout, "\tif (_rpcpmstart)\n");
	f_print(fout, "\t\tsyslog(LOG_ERR, \"%%s\", msg);\n");
	f_print(fout, "\telse\n");
	f_print(fout,
		"\t\t(void) fprintf(stderr, \"%%s\\n\", msg);\n");
	f_print(fout, "#else\n");
	f_print(fout, "\tsyslog(LOG_ERR, \"%%s\", msg);\n");
	f_print(fout, "#endif\n");
	f_print(fout, "}\n");
}