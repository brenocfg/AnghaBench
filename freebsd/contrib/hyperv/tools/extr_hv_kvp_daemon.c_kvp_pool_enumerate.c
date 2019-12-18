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
struct kvp_record {int /*<<< orphan*/  value; int /*<<< orphan*/  key; } ;
typedef  int /*<<< orphan*/  __u8 ;
struct TYPE_2__ {int num_records; struct kvp_record* records; } ;

/* Variables and functions */
 int /*<<< orphan*/  KVP_LOG (int /*<<< orphan*/ ,char*,int,int) ; 
 int /*<<< orphan*/  LOG_DEBUG ; 
 TYPE_1__* kvp_pools ; 
 int /*<<< orphan*/  kvp_update_mem_state (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
kvp_pool_enumerate(int pool, int idx, __u8 *key, int key_size,
    __u8 *value, int value_size)
{
	struct kvp_record *record;

	KVP_LOG(LOG_DEBUG, "kvp_pool_enumerate: pool = %d, index = %d\n,",
	    pool, idx);

	/* First update our in-memory state first. */
	kvp_update_mem_state(pool);
	record = kvp_pools[pool].records;

	/* Index starts with 0 */
	if (idx >= kvp_pools[pool].num_records) {
		return (1);
	}

	memcpy(key, record[idx].key, key_size);
	memcpy(value, record[idx].value, value_size);
	return (0);
}