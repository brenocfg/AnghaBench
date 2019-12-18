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
struct mtx {int dummy; } ;

/* Variables and functions */
 int MAX (int,int) ; 
 int /*<<< orphan*/  M_IPSEC_SPDCACHE ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int /*<<< orphan*/  SPDCACHE_LOCK_INIT (int) ; 
 int SPDCACHE_MAX_ENTRIES_PER_HASH ; 
 int /*<<< orphan*/  TUNABLE_INT_FETCH (char*,int*) ; 
 int V_key_spdcache_maxentries ; 
 int V_key_spdcache_threshold ; 
 int /*<<< orphan*/  V_spdcache_lock ; 
 int V_spdcachehash_mask ; 
 int /*<<< orphan*/  V_spdcachehashtbl ; 
 int /*<<< orphan*/  hashinit (int,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  malloc (int,int /*<<< orphan*/ ,int) ; 

void
spdcache_init(void)
{
	int i;

	TUNABLE_INT_FETCH("net.key.spdcache.maxentries",
	    &V_key_spdcache_maxentries);
	TUNABLE_INT_FETCH("net.key.spdcache.threshold",
	    &V_key_spdcache_threshold);

	if (V_key_spdcache_maxentries) {
		V_key_spdcache_maxentries = MAX(V_key_spdcache_maxentries,
		    SPDCACHE_MAX_ENTRIES_PER_HASH);
		V_spdcachehashtbl = hashinit(V_key_spdcache_maxentries /
		    SPDCACHE_MAX_ENTRIES_PER_HASH,
		    M_IPSEC_SPDCACHE, &V_spdcachehash_mask);
		V_key_spdcache_maxentries = (V_spdcachehash_mask + 1)
		    * SPDCACHE_MAX_ENTRIES_PER_HASH;

		V_spdcache_lock = malloc(sizeof(struct mtx) *
		    (V_spdcachehash_mask + 1),
		    M_IPSEC_SPDCACHE, M_WAITOK|M_ZERO);

		for (i = 0; i < V_spdcachehash_mask + 1; ++i)
			SPDCACHE_LOCK_INIT(i);
	}
}