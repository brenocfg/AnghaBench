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
struct set_gitdir_args {int /*<<< orphan*/ * member_0; } ;
struct repository {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (char*) ; 
 char* real_pathdup (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  repo_set_gitdir (struct repository*,char const*,struct set_gitdir_args*) ; 
 char* resolve_gitdir_gently (char*,int*) ; 

__attribute__((used)) static int repo_init_gitdir(struct repository *repo, const char *gitdir)
{
	int ret = 0;
	int error = 0;
	char *abspath = NULL;
	const char *resolved_gitdir;
	struct set_gitdir_args args = { NULL };

	abspath = real_pathdup(gitdir, 0);
	if (!abspath) {
		ret = -1;
		goto out;
	}

	/* 'gitdir' must reference the gitdir directly */
	resolved_gitdir = resolve_gitdir_gently(abspath, &error);
	if (!resolved_gitdir) {
		ret = -1;
		goto out;
	}

	repo_set_gitdir(repo, resolved_gitdir, &args);

out:
	free(abspath);
	return ret;
}