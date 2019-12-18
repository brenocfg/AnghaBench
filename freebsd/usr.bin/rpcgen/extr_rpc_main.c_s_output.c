#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ def_kind; } ;
typedef  TYPE_1__ definition ;

/* Variables and functions */
 scalar_t__ DEF_PROGRAM ; 
 int /*<<< orphan*/  add_warning () ; 
 int /*<<< orphan*/  do_registers (int,char const**) ; 
 int exitnow ; 
 char const* extendfile (char const*,char const*) ; 
 int /*<<< orphan*/  f_print (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  fout ; 
 int /*<<< orphan*/  free (char*) ; 
 TYPE_1__* get_definition () ; 
 int indefinitewait ; 
 scalar_t__ inetdflag ; 
 scalar_t__ logflag ; 
 int /*<<< orphan*/  open_input (char const*,char const*) ; 
 int /*<<< orphan*/  open_output (char const*,char const*) ; 
 scalar_t__ pmflag ; 
 scalar_t__ strcmp (char*,char*) ; 
 char* svcclosetime ; 
 int timerflag ; 
 scalar_t__ tirpcflag ; 
 int /*<<< orphan*/  unlink (char const*) ; 
 int /*<<< orphan*/  usage () ; 
 int /*<<< orphan*/  write_most (char const*,int,int) ; 
 int /*<<< orphan*/  write_rest () ; 

__attribute__((used)) static void
s_output(int argc, const char *argv[], const char *infile, const char *define,
    int extend, const char *outfile, int nomain, int netflag)
{
	char *include;
	definition *def;
	int foundprogram = 0;
	const char *outfilename;

	open_input(infile, define);
	outfilename = extend ? extendfile(infile, outfile) : outfile;
	open_output(infile, outfilename);
	add_warning();
	if (infile && (include = extendfile(infile, ".h"))) {
		f_print(fout, "#include \"%s\"\n", include);
		free(include);
	} else
		f_print(fout, "#include <rpc/rpc.h>\n");

	f_print(fout, "#include <stdio.h>\n");
	f_print(fout, "#include <stdlib.h> /* getenv, exit */\n");
	f_print (fout, "#include <rpc/pmap_clnt.h> /* for pmap_unset */\n");
	f_print (fout, "#include <string.h> /* strcmp */\n");
	if (tirpcflag)
		f_print(fout, "#include <rpc/rpc_com.h>\n");
	if (strcmp(svcclosetime, "-1") == 0)
		indefinitewait = 1;
	else if (strcmp(svcclosetime, "0") == 0)
		exitnow = 1;
	else if (inetdflag || pmflag) {
		f_print(fout, "#include <signal.h>\n");
		timerflag = 1;
	}

	if (!tirpcflag && inetdflag)
		f_print(fout, "#include <sys/ttycom.h> /* TIOCNOTTY */\n");
	if (inetdflag || pmflag) {
		f_print(fout, "#ifdef __cplusplus\n");
		f_print(fout,
			"#include <sys/sysent.h> /* getdtablesize, open */\n");
		f_print(fout, "#endif /* __cplusplus */\n");
	}
	if (tirpcflag) {
		f_print(fout, "#include <fcntl.h> /* open */\n");
		f_print(fout, "#include <unistd.h> /* fork / setsid */\n");
		f_print(fout, "#include <sys/types.h>\n");
	}

	f_print(fout, "#include <string.h>\n");
	if (inetdflag || !tirpcflag) {
		f_print(fout, "#include <sys/socket.h>\n");
		f_print(fout, "#include <netinet/in.h>\n");
	}

	if ((netflag || pmflag) && tirpcflag && !nomain) {
		f_print(fout, "#include <netconfig.h>\n");
	}
	if (tirpcflag)
		f_print(fout, "#include <sys/resource.h> /* rlimit */\n");
	if (logflag || inetdflag || pmflag || tirpcflag)
		f_print(fout, "#include <syslog.h>\n");

	f_print(fout, "\n#ifdef DEBUG\n#define	RPC_SVC_FG\n#endif\n");
	if (timerflag)
		f_print(fout, "\n#define	_RPCSVC_CLOSEDOWN %s\n",
			svcclosetime);
	while ( (def = get_definition()) ) {
		foundprogram |= (def->def_kind == DEF_PROGRAM);
	}
	if (extend && !foundprogram) {
		(void) unlink(outfilename);
		return;
	}
	write_most(infile, netflag, nomain);
	if (!nomain) {
		if (!do_registers(argc, argv)) {
			if (outfilename)
				(void) unlink(outfilename);
			usage();
		}
		write_rest();
	}
}