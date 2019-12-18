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
 int /*<<< orphan*/  KVP_LOG (int /*<<< orphan*/ ,char*,int,...) ; 
 int /*<<< orphan*/  LOG_DEBUG ; 
 TYPE_1__* kvp_pools ; 
 int /*<<< orphan*/  kvp_update_file (int) ; 
 int /*<<< orphan*/  kvp_update_mem_state (int) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
kvp_key_delete(int pool, __u8 *key, int key_size)
{
	int i;
	int j, k;
	int num_records;
	struct kvp_record *record;

	KVP_LOG(LOG_DEBUG, "kvp_key_delete: pool =  %d, "
	    "key = %s\n", pool, key);

	/* Update in-memory state */
	kvp_update_mem_state(pool);

	num_records = kvp_pools[pool].num_records;
	record = kvp_pools[pool].records;

	for (i = 0; i < num_records; i++)
	{
		if (memcmp(key, record[i].key, key_size)) {
			continue;
		}

		KVP_LOG(LOG_DEBUG, "Found delete key in pool %d.\n",
		    pool);
		/*
		 * We found a match at the end; Just update the number of
		 * entries and we are done.
		 */
		if (i == num_records) {
			kvp_pools[pool].num_records--;
			kvp_update_file(pool);
			return (0);
		}

		/*
		 * We found a match in the middle; Move the remaining
		 * entries up.
		 */
		j = i;
		k = j + 1;
		for ( ; k < num_records; k++)
		{
			strcpy(record[j].key, record[k].key);
			strcpy(record[j].value, record[k].value);
			j++;
		}
		kvp_pools[pool].num_records--;
		kvp_update_file(pool);
		return (0);
	}
	KVP_LOG(LOG_DEBUG, "Not found delete key in pool %d.\n",
	    pool);
	return (1);
}