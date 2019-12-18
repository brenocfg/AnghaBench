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
struct traverse_info {int dummy; } ;
struct name_entry {int /*<<< orphan*/  mode; int /*<<< orphan*/  pathlen; int /*<<< orphan*/  path; } ;
struct cache_entry {int dummy; } ;

/* Variables and functions */
 scalar_t__ ce_namelen (struct cache_entry const*) ; 
 int do_compare_entry (struct cache_entry const*,struct traverse_info const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ traverse_path_len (struct traverse_info const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tree_entry_len (struct name_entry const*) ; 

__attribute__((used)) static int compare_entry(const struct cache_entry *ce, const struct traverse_info *info, const struct name_entry *n)
{
	int cmp = do_compare_entry(ce, info, n->path, n->pathlen, n->mode);
	if (cmp)
		return cmp;

	/*
	 * Even if the beginning compared identically, the ce should
	 * compare as bigger than a directory leading up to it!
	 */
	return ce_namelen(ce) > traverse_path_len(info, tree_entry_len(n));
}