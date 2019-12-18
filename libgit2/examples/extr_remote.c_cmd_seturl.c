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
 int /*<<< orphan*/  check_lg2 (int,char*,char*) ; 
 int git_remote_set_pushurl (int /*<<< orphan*/ *,char*,char*) ; 
 int git_remote_set_url (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 int /*<<< orphan*/  usage (char*,char*) ; 

__attribute__((used)) static int cmd_seturl(git_repository *repo, struct opts *o)
{
	int i, retval, push = 0;
	char *name = NULL, *url = NULL;

	for (i = 0; i < o->argc; i++) {
		char *arg = o->argv[i];

		if (!strcmp(arg, "--push")) {
			push = 1;
		} else if (arg[0] != '-' && name == NULL) {
			name = arg;
		} else if (arg[0] != '-' && url == NULL) {
			url = arg;
		} else {
			usage("invalid argument to set-url", arg);
		}
	}

	if (name == NULL || url == NULL)
		usage("you need to specify remote and the new URL", NULL);

	if (push)
		retval = git_remote_set_pushurl(repo, name, url);
	else
		retval = git_remote_set_url(repo, name, url);

	check_lg2(retval, "could not set URL", url);

	return 0;
}