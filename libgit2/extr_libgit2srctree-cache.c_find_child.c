#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {size_t children_count; size_t namelen; int /*<<< orphan*/  name; struct TYPE_4__** children; } ;
typedef  TYPE_1__ git_tree_cache ;

/* Variables and functions */
 int /*<<< orphan*/  memcmp (char const*,int /*<<< orphan*/ ,size_t) ; 
 size_t strlen (char const*) ; 

__attribute__((used)) static git_tree_cache *find_child(
	const git_tree_cache *tree, const char *path, const char *end)
{
	size_t i, dirlen = end ? (size_t)(end - path) : strlen(path);

	for (i = 0; i < tree->children_count; ++i) {
		git_tree_cache *child = tree->children[i];

		if (child->namelen == dirlen && !memcmp(path, child->name, dirlen))
			return child;
	}

	return NULL;
}