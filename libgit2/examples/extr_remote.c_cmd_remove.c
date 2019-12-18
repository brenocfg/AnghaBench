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
struct opts {int argc; char** argv; } ;
typedef  int /*<<< orphan*/  git_repository ;

/* Variables and functions */
 int /*<<< orphan*/  check_lg2 (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  git_remote_delete (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  usage (char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int cmd_remove(git_repository *repo, struct opts *o)
{
	char *name;

	if (o->argc != 1)
		usage("you need to specify a name", NULL);

	name = o->argv[0];

	check_lg2(git_remote_delete(repo, name),
			"could not delete remote", name);

	return 0;
}