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
struct unpack_trees_options {TYPE_1__* src_index; } ;
struct traverse_info {struct unpack_trees_options* data; } ;
struct name_entry {int /*<<< orphan*/  pathlen; int /*<<< orphan*/  path; } ;
struct cache_entry {int dummy; } ;
struct TYPE_2__ {struct cache_entry** cache; } ;

/* Variables and functions */
 int find_cache_pos (struct traverse_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct cache_entry *find_cache_entry(struct traverse_info *info,
					    const struct name_entry *p)
{
	int pos = find_cache_pos(info, p->path, p->pathlen);
	struct unpack_trees_options *o = info->data;

	if (0 <= pos)
		return o->src_index->cache[pos];
	else
		return NULL;
}