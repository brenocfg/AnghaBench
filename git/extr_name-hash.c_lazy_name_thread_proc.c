#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct lazy_name_thread_data {TYPE_2__* istate; TYPE_1__* lazy_entries; } ;
struct cache_entry {int /*<<< orphan*/  ent; int /*<<< orphan*/  ce_flags; } ;
struct TYPE_4__ {int cache_nr; int /*<<< orphan*/  name_hash; struct cache_entry** cache; } ;
struct TYPE_3__ {int /*<<< orphan*/  hash_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  CE_HASHED ; 
 int /*<<< orphan*/  hashmap_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hashmap_entry_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void *lazy_name_thread_proc(void *_data)
{
	struct lazy_name_thread_data *d = _data;
	int k;

	for (k = 0; k < d->istate->cache_nr; k++) {
		struct cache_entry *ce_k = d->istate->cache[k];
		ce_k->ce_flags |= CE_HASHED;
		hashmap_entry_init(&ce_k->ent, d->lazy_entries[k].hash_name);
		hashmap_add(&d->istate->name_hash, &ce_k->ent);
	}

	return NULL;
}