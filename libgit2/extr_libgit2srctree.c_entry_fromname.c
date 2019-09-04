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
typedef  int /*<<< orphan*/  git_tree_entry ;
struct TYPE_4__ {int /*<<< orphan*/  entries; } ;
typedef  TYPE_1__ git_tree ;

/* Variables and functions */
 int /*<<< orphan*/  const* git_array_get (int /*<<< orphan*/ ,size_t) ; 
 scalar_t__ tree_key_search (size_t*,TYPE_1__ const*,char const*,size_t) ; 

__attribute__((used)) static const git_tree_entry *entry_fromname(
	const git_tree *tree, const char *name, size_t name_len)
{
	size_t idx;

	if (tree_key_search(&idx, tree, name, name_len) < 0)
		return NULL;

	return git_array_get(tree->entries, idx);
}