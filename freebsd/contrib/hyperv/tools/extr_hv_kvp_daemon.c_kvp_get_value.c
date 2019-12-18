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
 int HV_KVP_EXCHANGE_MAX_KEY_SIZE ; 
 int HV_KVP_EXCHANGE_MAX_VALUE_SIZE ; 
 int /*<<< orphan*/  KVP_LOG (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LOG_DEBUG ; 
 TYPE_1__* kvp_pools ; 
 int /*<<< orphan*/  kvp_update_mem_state (int) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
kvp_get_value(int pool, __u8 *key, int key_size, __u8 *value,
    int value_size)
{
	int i;
	int num_records;
	struct kvp_record *record;

	KVP_LOG(LOG_DEBUG, "kvp_get_value: pool =  %d, key = %s\n,",
	    pool, key);

	if ((key_size > HV_KVP_EXCHANGE_MAX_KEY_SIZE) ||
	    (value_size > HV_KVP_EXCHANGE_MAX_VALUE_SIZE)) {
		return (1);
	}

	/* Update the in-memory state first. */
	kvp_update_mem_state(pool);

	num_records = kvp_pools[pool].num_records;
	record = kvp_pools[pool].records;

	for (i = 0; i < num_records; i++)
	{
		if (memcmp(key, record[i].key, key_size)) {
			continue;
		}

		/* Found the key */
		memcpy(value, record[i].value, value_size);
		return (0);
	}

	return (1);
}