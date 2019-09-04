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
struct worktree {char* path; } ;

/* Variables and functions */
 int /*<<< orphan*/  fspathcmp (char const*,char const*) ; 
 scalar_t__ is_dir_sep (char const) ; 
 int strlen (char const*) ; 

__attribute__((used)) static struct worktree *find_worktree_by_suffix(struct worktree **list,
						const char *suffix)
{
	struct worktree *found = NULL;
	int nr_found = 0, suffixlen;

	suffixlen = strlen(suffix);
	if (!suffixlen)
		return NULL;

	for (; *list && nr_found < 2; list++) {
		const char	*path	 = (*list)->path;
		int		 pathlen = strlen(path);
		int		 start	 = pathlen - suffixlen;

		/* suffix must start at directory boundary */
		if ((!start || (start > 0 && is_dir_sep(path[start - 1]))) &&
		    !fspathcmp(suffix, path + start)) {
			found = *list;
			nr_found++;
		}
	}
	return nr_found == 1 ? found : NULL;
}