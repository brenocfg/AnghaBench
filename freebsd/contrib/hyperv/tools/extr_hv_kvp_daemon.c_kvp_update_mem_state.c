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
struct kvp_record {int dummy; } ;
struct TYPE_2__ {int num_blocks; size_t num_records; struct kvp_record* records; int /*<<< orphan*/  fname; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int ENTRIES_PER_BLOCK ; 
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int /*<<< orphan*/  KVP_LOG (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  feof (int /*<<< orphan*/ *) ; 
 scalar_t__ ferror (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ fread (struct kvp_record*,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kvp_acquire_lock (int) ; 
 TYPE_1__* kvp_pools ; 
 int /*<<< orphan*/  kvp_release_lock (int) ; 
 struct kvp_record* realloc (struct kvp_record*,int) ; 

__attribute__((used)) static void
kvp_update_mem_state(int pool)
{
	FILE *filep;
	size_t records_read = 0;
	struct kvp_record *record = kvp_pools[pool].records;
	struct kvp_record *readp;
	int num_blocks = kvp_pools[pool].num_blocks;
	int alloc_unit = sizeof(struct kvp_record) * ENTRIES_PER_BLOCK;

	kvp_acquire_lock(pool);

	filep = fopen(kvp_pools[pool].fname, "r");
	if (!filep) {
		kvp_release_lock(pool);
		KVP_LOG(LOG_ERR, "Failed to open file, pool: %d\n", pool);
		exit(EXIT_FAILURE);
	}
	for ( ; ; )
	{
		readp = &record[records_read];
		records_read += fread(readp, sizeof(struct kvp_record),
			ENTRIES_PER_BLOCK * num_blocks,
			filep);

		if (ferror(filep)) {
			KVP_LOG(LOG_ERR, "Failed to read file, pool: %d\n", pool);
			exit(EXIT_FAILURE);
		}

		if (!feof(filep)) {
			/*
			 * Have more data to read. Expand the memory.
			 */
			num_blocks++;
			record = realloc(record, alloc_unit * num_blocks);

			if (record == NULL) {
				KVP_LOG(LOG_ERR, "malloc failed\n");
				exit(EXIT_FAILURE);
			}
			continue;
		}
		break;
	}

	kvp_pools[pool].num_blocks = num_blocks;
	kvp_pools[pool].records = record;
	kvp_pools[pool].num_records = records_read;

	fclose(filep);
	kvp_release_lock(pool);
}