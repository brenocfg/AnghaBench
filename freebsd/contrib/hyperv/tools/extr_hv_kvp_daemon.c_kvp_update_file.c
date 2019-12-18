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
struct TYPE_2__ {int /*<<< orphan*/  num_records; int /*<<< orphan*/  records; int /*<<< orphan*/  fname; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int /*<<< orphan*/  KVP_LOG (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 scalar_t__ fclose (int /*<<< orphan*/ *) ; 
 scalar_t__ ferror (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (int /*<<< orphan*/ ,char*) ; 
 size_t fwrite (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kvp_acquire_lock (int) ; 
 TYPE_1__* kvp_pools ; 
 int /*<<< orphan*/  kvp_release_lock (int) ; 

__attribute__((used)) static void
kvp_update_file(int pool)
{
	FILE *filep;
	size_t bytes_written;

	kvp_acquire_lock(pool);

	filep = fopen(kvp_pools[pool].fname, "w");
	if (!filep) {
		kvp_release_lock(pool);
		KVP_LOG(LOG_ERR, "Failed to open file, pool: %d\n", pool);
		exit(EXIT_FAILURE);
	}

	bytes_written = fwrite(kvp_pools[pool].records,
		sizeof(struct kvp_record),
		kvp_pools[pool].num_records, filep);

	if (ferror(filep) || fclose(filep)) {
		kvp_release_lock(pool);
		KVP_LOG(LOG_ERR, "Failed to write file, pool: %d\n", pool);
		exit(EXIT_FAILURE);
	}

	kvp_release_lock(pool);
}