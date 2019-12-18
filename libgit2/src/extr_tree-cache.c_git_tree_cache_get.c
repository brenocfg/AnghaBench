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
typedef  int /*<<< orphan*/  git_tree_cache ;

/* Variables and functions */
 int /*<<< orphan*/ * find_child (int /*<<< orphan*/  const*,char const*,char const*) ; 
 char* strchr (char const*,char) ; 

const git_tree_cache *git_tree_cache_get(const git_tree_cache *tree, const char *path)
{
	const char *ptr = path, *end;

	if (tree == NULL) {
		return NULL;
	}

	while (1) {
		end = strchr(ptr, '/');

		tree = find_child(tree, ptr, end);
		if (tree == NULL) /* Can't find it */
			return NULL;

		if (end == NULL || *end + 1 == '\0')
			return tree;

		ptr = end + 1;
	}
}