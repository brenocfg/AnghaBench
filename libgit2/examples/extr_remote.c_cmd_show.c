#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct opts {int argc; char** argv; } ;
struct TYPE_6__ {char** strings; scalar_t__ count; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_2__ git_strarray ;
typedef  int /*<<< orphan*/  git_repository ;
typedef  int /*<<< orphan*/  git_remote ;
struct TYPE_5__ {int /*<<< orphan*/  member_0; } ;

/* Variables and functions */
 int /*<<< orphan*/  check_lg2 (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  git_remote_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_remote_list (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_remote_lookup (int /*<<< orphan*/ **,int /*<<< orphan*/ *,char const*) ; 
 char* git_remote_pushurl (int /*<<< orphan*/ *) ; 
 char* git_remote_url (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_strarray_free (TYPE_2__*) ; 
 int /*<<< orphan*/  printf (char*,char const*,char const*) ; 
 int /*<<< orphan*/  puts (char const*) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 

__attribute__((used)) static int cmd_show(git_repository *repo, struct opts *o)
{
	int i;
	const char *arg, *name, *fetch, *push;
	int verbose = 0;
	git_strarray remotes = {0};
	git_remote *remote = {0};

	for (i = 0; i < o->argc; i++) {
		arg = o->argv[i];

		if (!strcmp(arg, "-v") || !strcmp(arg, "--verbose")) {
			verbose = 1;
		}
	}

	check_lg2(git_remote_list(&remotes, repo),
		"could not retrieve remotes", NULL);

	for (i = 0; i < (int) remotes.count; i++) {
		name = remotes.strings[i];
		if (!verbose) {
			puts(name);
			continue;
		}

		check_lg2(git_remote_lookup(&remote, repo, name),
			"could not look up remote", name);

		fetch = git_remote_url(remote);
		if (fetch)
			printf("%s\t%s (fetch)\n", name, fetch);
		push = git_remote_pushurl(remote);
		/* use fetch URL if no distinct push URL has been set */
		push = push ? push : fetch;
		if (push)
			printf("%s\t%s (push)\n", name, push);

		git_remote_free(remote);
	}

	git_strarray_free(&remotes);

	return 0;
}