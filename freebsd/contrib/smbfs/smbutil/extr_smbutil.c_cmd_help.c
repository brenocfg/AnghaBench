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
struct commands {int /*<<< orphan*/  (* usage ) () ;} ;

/* Variables and functions */
 int /*<<< orphan*/  EX_DATAERR ; 
 int /*<<< orphan*/  errx (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  help_usage () ; 
 struct commands* lookupcmd (char*) ; 
 int /*<<< orphan*/  stub1 () ; 

int
cmd_help(int argc, char *argv[])
{
	struct commands *cmd;
	char *cp;
    
	if (argc < 2)
		help_usage();
	cp = argv[1];
	cmd = lookupcmd(cp);
	if (cmd == NULL)
		errx(EX_DATAERR, "unknown command %s", cp);
	if (cmd->usage == NULL)
		errx(EX_DATAERR, "no specific help for command %s", cp);
	cmd->usage();
	exit(0);
}