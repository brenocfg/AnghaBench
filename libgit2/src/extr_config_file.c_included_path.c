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
typedef  int /*<<< orphan*/  git_buf ;

/* Variables and functions */
 int git_path_join_unrooted (int /*<<< orphan*/ *,char const*,char const*,int /*<<< orphan*/ *) ; 
 int git_sysdir_expand_global_file (int /*<<< orphan*/ *,char const*) ; 

__attribute__((used)) static int included_path(git_buf *out, const char *dir, const char *path)
{
	/* From the user's home */
	if (path[0] == '~' && path[1] == '/')
		return git_sysdir_expand_global_file(out, &path[1]);

	return git_path_join_unrooted(out, path, dir, NULL);
}