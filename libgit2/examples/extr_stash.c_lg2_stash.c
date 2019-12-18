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
struct opts {int cmd; int /*<<< orphan*/  member_0; } ;
typedef  int /*<<< orphan*/  git_repository ;

/* Variables and functions */
#define  SUBCMD_APPLY 131 
#define  SUBCMD_LIST 130 
#define  SUBCMD_POP 129 
#define  SUBCMD_PUSH 128 
 int cmd_apply (int /*<<< orphan*/ *,struct opts*) ; 
 int cmd_list (int /*<<< orphan*/ *,struct opts*) ; 
 int cmd_pop (int /*<<< orphan*/ *,struct opts*) ; 
 int cmd_push (int /*<<< orphan*/ *,struct opts*) ; 
 int /*<<< orphan*/  parse_subcommand (struct opts*,int,char**) ; 

int lg2_stash(git_repository *repo, int argc, char *argv[])
{
	struct opts opts = { 0 };

	parse_subcommand(&opts, argc, argv);

	switch (opts.cmd) {
		case SUBCMD_APPLY:
			return cmd_apply(repo, &opts);
		case SUBCMD_LIST:
			return cmd_list(repo, &opts);
		case SUBCMD_PUSH:
			return cmd_push(repo, &opts);
		case SUBCMD_POP:
			return cmd_pop(repo, &opts);
	}

	return -1;
}