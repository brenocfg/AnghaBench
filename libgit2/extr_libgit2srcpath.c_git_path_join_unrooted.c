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
typedef  scalar_t__ ssize_t ;
typedef  int /*<<< orphan*/  git_buf ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ git_buf_joinpath (int /*<<< orphan*/ *,char const*,char const*) ; 
 scalar_t__ git_buf_sets (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  git_path_equal_or_prefixed (char const*,char const*,scalar_t__*) ; 
 scalar_t__ git_path_root (char const*) ; 
 scalar_t__ strlen (char const*) ; 

int git_path_join_unrooted(
	git_buf *path_out, const char *path, const char *base, ssize_t *root_at)
{
	ssize_t root;

	assert(path && path_out);

	root = (ssize_t)git_path_root(path);

	if (base != NULL && root < 0) {
		if (git_buf_joinpath(path_out, base, path) < 0)
			return -1;

		root = (ssize_t)strlen(base);
	} else {
		if (git_buf_sets(path_out, path) < 0)
			return -1;

		if (root < 0)
			root = 0;
		else if (base)
			git_path_equal_or_prefixed(base, path, &root);
	}

	if (root_at)
		*root_at = root;

	return 0;
}