#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {size_t namelen; char* name; } ;
typedef  TYPE_1__ git_tree_cache ;
typedef  int /*<<< orphan*/  git_pool ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_ERROR_CHECK_ALLOC (TYPE_1__*) ; 
 TYPE_1__* git_pool_malloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,size_t) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int,int) ; 
 size_t strlen (char const*) ; 

int git_tree_cache_new(git_tree_cache **out, const char *name, git_pool *pool)
{
	size_t name_len;
	git_tree_cache *tree;

	name_len = strlen(name);
	tree = git_pool_malloc(pool, sizeof(git_tree_cache) + name_len + 1);
	GIT_ERROR_CHECK_ALLOC(tree);

	memset(tree, 0x0, sizeof(git_tree_cache));
	/* NUL-terminated tree name */
	tree->namelen = name_len;
	memcpy(tree->name, name, name_len);
	tree->name[name_len] = '\0';

	*out = tree;
	return 0;
}