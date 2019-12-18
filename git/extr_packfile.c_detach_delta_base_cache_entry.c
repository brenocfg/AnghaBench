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
struct delta_base_cache_entry {scalar_t__ size; int /*<<< orphan*/  lru; int /*<<< orphan*/  key; int /*<<< orphan*/  ent; } ;

/* Variables and functions */
 int /*<<< orphan*/  delta_base_cache ; 
 int /*<<< orphan*/  delta_base_cached ; 
 int /*<<< orphan*/  free (struct delta_base_cache_entry*) ; 
 int /*<<< orphan*/  hashmap_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void detach_delta_base_cache_entry(struct delta_base_cache_entry *ent)
{
	hashmap_remove(&delta_base_cache, &ent->ent, &ent->key);
	list_del(&ent->lru);
	delta_base_cached -= ent->size;
	free(ent);
}