#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct opts {int argc; char** argv; } ;
struct TYPE_4__ {int /*<<< orphan*/ * strings; scalar_t__ count; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ git_strarray ;
typedef  int /*<<< orphan*/  git_repository ;

/* Variables and functions */
 int git_remote_rename (TYPE_1__*,int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  git_strarray_free (TYPE_1__*) ; 
 int /*<<< orphan*/  puts (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usage (char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int cmd_rename(git_repository *repo, struct opts *o)
{
	int i, retval;
	char *old, *new;
	git_strarray problems = {0};

	if (o->argc != 2)
		usage("you need to specify old and new remote name", NULL);

	old = o->argv[0];
	new = o->argv[1];

	retval = git_remote_rename(&problems, repo, old, new);
	if (!retval)
		return 0;

	for (i = 0; i < (int) problems.count; i++) {
		puts(problems.strings[0]);
	}

	git_strarray_free(&problems);

	return retval;
}