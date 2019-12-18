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

/* Variables and functions */
 int /*<<< orphan*/  H_SET_PARTITION_TABLE ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 scalar_t__ kvmhv_on_pseries () ; 
 int /*<<< orphan*/  plpar_hcall_norets (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pseries_partition_tb ; 

void kvmhv_nested_exit(void)
{
	/*
	 * N.B. the kvmhv_on_pseries() test is there because it enables
	 * the compiler to remove the call to plpar_hcall_norets()
	 * when CONFIG_PPC_PSERIES=n.
	 */
	if (kvmhv_on_pseries() && pseries_partition_tb) {
		plpar_hcall_norets(H_SET_PARTITION_TABLE, 0);
		kfree(pseries_partition_tb);
		pseries_partition_tb = NULL;
	}
}