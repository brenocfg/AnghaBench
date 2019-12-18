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
struct parsed_partitions {int dummy; } ;
struct TYPE_2__ {unsigned long config_start; } ;
struct ldmdb {int /*<<< orphan*/  v_part; int /*<<< orphan*/  v_comp; int /*<<< orphan*/  v_volu; int /*<<< orphan*/  v_disk; int /*<<< orphan*/  v_dgrp; TYPE_1__ ph; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct ldmdb*) ; 
 struct ldmdb* kmalloc (int,int /*<<< orphan*/ ) ; 
 scalar_t__ ldm_create_data_partitions (struct parsed_partitions*,struct ldmdb*) ; 
 int /*<<< orphan*/  ldm_crit (char*) ; 
 int /*<<< orphan*/  ldm_debug (char*) ; 
 int /*<<< orphan*/  ldm_free_vblks (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ldm_get_vblks (struct parsed_partitions*,unsigned long,struct ldmdb*) ; 
 int /*<<< orphan*/  ldm_validate_partition_table (struct parsed_partitions*) ; 
 int /*<<< orphan*/  ldm_validate_privheads (struct parsed_partitions*,TYPE_1__*) ; 
 int /*<<< orphan*/  ldm_validate_tocblocks (struct parsed_partitions*,unsigned long,struct ldmdb*) ; 
 int /*<<< orphan*/  ldm_validate_vmdb (struct parsed_partitions*,unsigned long,struct ldmdb*) ; 

int ldm_partition(struct parsed_partitions *state)
{
	struct ldmdb  *ldb;
	unsigned long base;
	int result = -1;

	BUG_ON(!state);

	/* Look for signs of a Dynamic Disk */
	if (!ldm_validate_partition_table(state))
		return 0;

	ldb = kmalloc (sizeof (*ldb), GFP_KERNEL);
	if (!ldb) {
		ldm_crit ("Out of memory.");
		goto out;
	}

	/* Parse and check privheads. */
	if (!ldm_validate_privheads(state, &ldb->ph))
		goto out;		/* Already logged */

	/* All further references are relative to base (database start). */
	base = ldb->ph.config_start;

	/* Parse and check tocs and vmdb. */
	if (!ldm_validate_tocblocks(state, base, ldb) ||
	    !ldm_validate_vmdb(state, base, ldb))
	    	goto out;		/* Already logged */

	/* Initialize vblk lists in ldmdb struct */
	INIT_LIST_HEAD (&ldb->v_dgrp);
	INIT_LIST_HEAD (&ldb->v_disk);
	INIT_LIST_HEAD (&ldb->v_volu);
	INIT_LIST_HEAD (&ldb->v_comp);
	INIT_LIST_HEAD (&ldb->v_part);

	if (!ldm_get_vblks(state, base, ldb)) {
		ldm_crit ("Failed to read the VBLKs from the database.");
		goto cleanup;
	}

	/* Finally, create the data partition devices. */
	if (ldm_create_data_partitions(state, ldb)) {
		ldm_debug ("Parsed LDM database successfully.");
		result = 1;
	}
	/* else Already logged */

cleanup:
	ldm_free_vblks (&ldb->v_dgrp);
	ldm_free_vblks (&ldb->v_disk);
	ldm_free_vblks (&ldb->v_volu);
	ldm_free_vblks (&ldb->v_comp);
	ldm_free_vblks (&ldb->v_part);
out:
	kfree (ldb);
	return result;
}