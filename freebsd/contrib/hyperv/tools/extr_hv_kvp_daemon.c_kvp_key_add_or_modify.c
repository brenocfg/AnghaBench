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
struct kvp_record {int /*<<< orphan*/  key; int /*<<< orphan*/  value; } ;
typedef  int /*<<< orphan*/  __u8 ;
typedef  int /*<<< orphan*/  __u32 ;
struct TYPE_2__ {int num_records; int num_blocks; struct kvp_record* records; } ;

/* Variables and functions */
 int ENTRIES_PER_BLOCK ; 
 int /*<<< orphan*/  HV_KVP_EXCHANGE_MAX_KEY_SIZE ; 
 int /*<<< orphan*/  HV_KVP_EXCHANGE_MAX_VALUE_SIZE ; 
 int /*<<< orphan*/  KVP_LOG (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  LOG_DEBUG ; 
 int /*<<< orphan*/  LOG_ERR ; 
 TYPE_1__* kvp_pools ; 
 int /*<<< orphan*/  kvp_update_file (int) ; 
 int /*<<< orphan*/  kvp_update_mem_state (int) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct kvp_record* realloc (struct kvp_record*,int) ; 

__attribute__((used)) static int
kvp_key_add_or_modify(int pool, __u8 *key, __u32 key_size, __u8 *value,
    __u32 value_size)
{
	int i;
	int num_records;
	struct kvp_record *record;
	int num_blocks;

	KVP_LOG(LOG_DEBUG, "kvp_key_add_or_modify: pool =  %d, "
	    "key = %s, value = %s\n,", pool, key, value);

	if ((key_size > HV_KVP_EXCHANGE_MAX_KEY_SIZE) ||
	    (value_size > HV_KVP_EXCHANGE_MAX_VALUE_SIZE)) {
		KVP_LOG(LOG_ERR, "kvp_key_add_or_modify: returning 1\n");
		return (1);
	}

	/* Update the in-memory state. */
	kvp_update_mem_state(pool);

	num_records = kvp_pools[pool].num_records;
	record = kvp_pools[pool].records;
	num_blocks = kvp_pools[pool].num_blocks;

	for (i = 0; i < num_records; i++)
	{
		if (memcmp(key, record[i].key, key_size)) {
			continue;
		}

		/*
		 * Key exists. Just update the value and we are done.
		 */
		memcpy(record[i].value, value, value_size);
		kvp_update_file(pool);
		return (0);
	}

	/*
	 * Key doesn't exist; Add a new KVP.
	 */
	if (num_records == (ENTRIES_PER_BLOCK * num_blocks)) {
		/* Increase the size of the recodrd array. */
		record = realloc(record, sizeof(struct kvp_record) *
			ENTRIES_PER_BLOCK * (num_blocks + 1));

		if (record == NULL) {
			return (1);
		}
		kvp_pools[pool].num_blocks++;
	}
	memcpy(record[i].value, value, value_size);
	memcpy(record[i].key, key, key_size);
	kvp_pools[pool].records = record;
	kvp_pools[pool].num_records++;
	kvp_update_file(pool);
	return (0);
}