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
 int cmd_add (int /*<<< orphan*/ *,struct opts*) ; 
 int cmd_remove (int /*<<< orphan*/ *,struct opts*) ; 
 int cmd_rename (int /*<<< orphan*/ *,struct opts*) ; 
 int cmd_seturl (int /*<<< orphan*/ *,struct opts*) ; 
 int cmd_show (int /*<<< orphan*/ *,struct opts*) ; 
 int /*<<< orphan*/  parse_subcmd (struct opts*,int,char**) ; 
#define  subcmd_add 132 
#define  subcmd_remove 131 
#define  subcmd_rename 130 
#define  subcmd_seturl 129 
#define  subcmd_show 128 

int lg2_remote(git_repository *repo, int argc, char *argv[])
{
	int retval = 0;
	struct opts opt = {0};

	parse_subcmd(&opt, argc, argv);

	switch (opt.cmd)
	{
	case subcmd_add:
		retval = cmd_add(repo, &opt);
		break;
	case subcmd_remove:
		retval = cmd_remove(repo, &opt);
		break;
	case subcmd_rename:
		retval = cmd_rename(repo, &opt);
		break;
	case subcmd_seturl:
		retval = cmd_seturl(repo, &opt);
		break;
	case subcmd_show:
		retval = cmd_show(repo, &opt);
		break;
	}

	return retval;
}