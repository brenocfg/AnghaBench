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
struct cache_index_dir {struct cache_index_dir* next; int /*<<< orphan*/  kobj; struct cache* cache; } ;
struct cache_dir {struct cache_index_dir* index; int /*<<< orphan*/  kobj; } ;
struct cache {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  cache_index_type ; 
 int /*<<< orphan*/  cacheinfo_create_index_opt_attrs (struct cache_index_dir*) ; 
 int kobject_init_and_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  kobject_put (int /*<<< orphan*/ *) ; 
 struct cache_index_dir* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cacheinfo_create_index_dir(struct cache *cache, int index,
				       struct cache_dir *cache_dir)
{
	struct cache_index_dir *index_dir;
	int rc;

	index_dir = kzalloc(sizeof(*index_dir), GFP_KERNEL);
	if (!index_dir)
		return;

	index_dir->cache = cache;

	rc = kobject_init_and_add(&index_dir->kobj, &cache_index_type,
				  cache_dir->kobj, "index%d", index);
	if (rc) {
		kobject_put(&index_dir->kobj);
		return;
	}

	index_dir->next = cache_dir->index;
	cache_dir->index = index_dir;

	cacheinfo_create_index_opt_attrs(index_dir);
}