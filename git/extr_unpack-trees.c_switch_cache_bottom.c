#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct unpack_trees_options {int cache_bottom; TYPE_1__* src_index; scalar_t__ diff_index_cached; } ;
struct traverse_info {int /*<<< orphan*/  namelen; int /*<<< orphan*/  name; int /*<<< orphan*/  prev; struct unpack_trees_options* data; } ;
struct TYPE_2__ {int cache_nr; } ;

/* Variables and functions */
 int find_cache_pos (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int switch_cache_bottom(struct traverse_info *info)
{
	struct unpack_trees_options *o = info->data;
	int ret, pos;

	if (o->diff_index_cached)
		return 0;
	ret = o->cache_bottom;
	pos = find_cache_pos(info->prev, info->name, info->namelen);

	if (pos < -1)
		o->cache_bottom = -2 - pos;
	else if (pos < 0)
		o->cache_bottom = o->src_index->cache_nr;
	return ret;
}