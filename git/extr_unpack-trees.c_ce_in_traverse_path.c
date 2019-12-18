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
struct traverse_info {scalar_t__ pathlen; int /*<<< orphan*/  mode; int /*<<< orphan*/  namelen; int /*<<< orphan*/  name; int /*<<< orphan*/  prev; } ;
struct cache_entry {int dummy; } ;

/* Variables and functions */
 scalar_t__ ce_namelen (struct cache_entry const*) ; 
 scalar_t__ do_compare_entry (struct cache_entry const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ce_in_traverse_path(const struct cache_entry *ce,
			       const struct traverse_info *info)
{
	if (!info->prev)
		return 1;
	if (do_compare_entry(ce, info->prev,
			     info->name, info->namelen, info->mode))
		return 0;
	/*
	 * If ce (blob) is the same name as the path (which is a tree
	 * we will be descending into), it won't be inside it.
	 */
	return (info->pathlen < ce_namelen(ce));
}