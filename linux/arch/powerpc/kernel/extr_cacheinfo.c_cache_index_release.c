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
struct kobject {int dummy; } ;
struct cache_index_dir {TYPE_1__* cache; } ;
struct TYPE_2__ {int /*<<< orphan*/  level; } ;

/* Variables and functions */
 int /*<<< orphan*/  cache_type_string (TYPE_1__*) ; 
 int /*<<< orphan*/  kfree (struct cache_index_dir*) ; 
 struct cache_index_dir* kobj_to_cache_index_dir (struct kobject*) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cache_index_release(struct kobject *kobj)
{
	struct cache_index_dir *index;

	index = kobj_to_cache_index_dir(kobj);

	pr_debug("freeing index directory for L%d %s cache\n",
		 index->cache->level, cache_type_string(index->cache));

	kfree(index);
}