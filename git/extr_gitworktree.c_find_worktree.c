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
struct worktree {int /*<<< orphan*/  path; } ;

/* Variables and functions */
 struct worktree* find_worktree_by_suffix (struct worktree**,char const*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  fspathcmp (char*,int /*<<< orphan*/ ) ; 
 char* prefix_filename (char const*,char const*) ; 
 int /*<<< orphan*/  real_path (int /*<<< orphan*/ ) ; 
 char* real_pathdup (char const*,int /*<<< orphan*/ ) ; 

struct worktree *find_worktree(struct worktree **list,
			       const char *prefix,
			       const char *arg)
{
	struct worktree *wt;
	char *path;
	char *to_free = NULL;

	if ((wt = find_worktree_by_suffix(list, arg)))
		return wt;

	if (prefix)
		arg = to_free = prefix_filename(prefix, arg);
	path = real_pathdup(arg, 0);
	if (!path) {
		free(to_free);
		return NULL;
	}
	for (; *list; list++)
		if (!fspathcmp(path, real_path((*list)->path)))
			break;
	free(path);
	free(to_free);
	return *list;
}