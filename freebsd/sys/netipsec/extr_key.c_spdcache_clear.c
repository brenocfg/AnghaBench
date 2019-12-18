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
struct spdcache_entry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_EMPTY (int /*<<< orphan*/ *) ; 
 struct spdcache_entry* LIST_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LIST_REMOVE (struct spdcache_entry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SPDCACHE_LOCK (int) ; 
 int /*<<< orphan*/  SPDCACHE_UNLOCK (int) ; 
 int V_spdcachehash_mask ; 
 int /*<<< orphan*/ * V_spdcachehashtbl ; 
 int /*<<< orphan*/  chain ; 
 int /*<<< orphan*/  spdcache_entry_free (struct spdcache_entry*) ; 

void
spdcache_clear(void)
{
	struct spdcache_entry *entry;
	int i;

	for (i = 0; i < V_spdcachehash_mask + 1; ++i) {
		SPDCACHE_LOCK(i);
		while (!LIST_EMPTY(&V_spdcachehashtbl[i])) {
			entry = LIST_FIRST(&V_spdcachehashtbl[i]);
			LIST_REMOVE(entry, chain);
			spdcache_entry_free(entry);
		}
		SPDCACHE_UNLOCK(i);
	}
}