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
struct opts {int cmd; int argc; char** argv; } ;
typedef  enum subcmd { ____Placeholder_subcmd } subcmd ;

/* Variables and functions */
 int SUBCMD_APPLY ; 
 int SUBCMD_LIST ; 
 int SUBCMD_POP ; 
 int SUBCMD_PUSH ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 int /*<<< orphan*/  usage (char*,char*) ; 

__attribute__((used)) static void parse_subcommand(struct opts *opts, int argc, char *argv[])
{
	char *arg = (argc < 2) ? "push" : argv[1];
	enum subcmd cmd;

	if (!strcmp(arg, "apply")) {
		cmd = SUBCMD_APPLY;
	} else if (!strcmp(arg, "list")) {
		cmd = SUBCMD_LIST;
	} else if (!strcmp(arg, "pop")) {
		cmd = SUBCMD_POP;
	} else if (!strcmp(arg, "push")) {
		cmd = SUBCMD_PUSH;
	} else {
		usage("invalid command %s", arg);
		return;
	}

	opts->cmd = cmd;
	opts->argc = (argc < 2) ? argc - 1 : argc - 2;
	opts->argv = argv;
}