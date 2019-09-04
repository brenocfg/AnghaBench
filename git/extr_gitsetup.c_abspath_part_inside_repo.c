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
 scalar_t__ fspathcmp (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  fspathncmp (char*,char const*,size_t) ; 
 char* get_git_work_tree () ; 
 int /*<<< orphan*/  memmove (char*,char*,size_t) ; 
 int offset_1st_component (char*) ; 
 int /*<<< orphan*/  real_path (char*) ; 
 size_t strlen (char const*) ; 

__attribute__((used)) static int abspath_part_inside_repo(char *path)
{
	size_t len;
	size_t wtlen;
	char *path0;
	int off;
	const char *work_tree = get_git_work_tree();

	if (!work_tree)
		return -1;
	wtlen = strlen(work_tree);
	len = strlen(path);
	off = offset_1st_component(path);

	/* check if work tree is already the prefix */
	if (wtlen <= len && !fspathncmp(path, work_tree, wtlen)) {
		if (path[wtlen] == '/') {
			memmove(path, path + wtlen + 1, len - wtlen);
			return 0;
		} else if (path[wtlen - 1] == '/' || path[wtlen] == '\0') {
			/* work tree is the root, or the whole path */
			memmove(path, path + wtlen, len - wtlen + 1);
			return 0;
		}
		/* work tree might match beginning of a symlink to work tree */
		off = wtlen;
	}
	path0 = path;
	path += off;

	/* check each '/'-terminated level */
	while (*path) {
		path++;
		if (*path == '/') {
			*path = '\0';
			if (fspathcmp(real_path(path0), work_tree) == 0) {
				memmove(path0, path + 1, len - (path - path0));
				return 0;
			}
			*path = '/';
		}
	}

	/* check whole path */
	if (fspathcmp(real_path(path0), work_tree) == 0) {
		*path0 = '\0';
		return 0;
	}

	return -1;
}