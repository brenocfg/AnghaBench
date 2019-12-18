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

/* Variables and functions */
 scalar_t__ skip_prefix (char const*,char*,char const**) ; 
 char* strchr (char const*,char) ; 

int parse_worktree_ref(const char *worktree_ref, const char **name,
		       int *name_length, const char **ref)
{
	if (skip_prefix(worktree_ref, "main-worktree/", &worktree_ref)) {
		if (!*worktree_ref)
			return -1;
		if (name)
			*name = NULL;
		if (name_length)
			*name_length = 0;
		if (ref)
			*ref = worktree_ref;
		return 0;
	}
	if (skip_prefix(worktree_ref, "worktrees/", &worktree_ref)) {
		const char *slash = strchr(worktree_ref, '/');

		if (!slash || slash == worktree_ref || !slash[1])
			return -1;
		if (name)
			*name = worktree_ref;
		if (name_length)
			*name_length = slash - worktree_ref;
		if (ref)
			*ref = slash + 1;
		return 0;
	}
	return -1;
}