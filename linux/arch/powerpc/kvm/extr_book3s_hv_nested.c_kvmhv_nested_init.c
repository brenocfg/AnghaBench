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
struct patb_entry {int dummy; } ;

/* Variables and functions */
 long ENODEV ; 
 long ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  H_SET_PARTITION_TABLE ; 
 long H_SUCCESS ; 
 scalar_t__ KVMPPC_NR_LPIDS ; 
 int __ilog2 (scalar_t__) ; 
 long __pa (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvmhv_on_pseries () ; 
 long plpar_hcall_norets (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 
 int /*<<< orphan*/ * pseries_partition_tb ; 
 int /*<<< orphan*/  radix_enabled () ; 

long kvmhv_nested_init(void)
{
	long int ptb_order;
	unsigned long ptcr;
	long rc;

	if (!kvmhv_on_pseries())
		return 0;
	if (!radix_enabled())
		return -ENODEV;

	/* find log base 2 of KVMPPC_NR_LPIDS, rounding up */
	ptb_order = __ilog2(KVMPPC_NR_LPIDS - 1) + 1;
	if (ptb_order < 8)
		ptb_order = 8;
	pseries_partition_tb = kmalloc(sizeof(struct patb_entry) << ptb_order,
				       GFP_KERNEL);
	if (!pseries_partition_tb) {
		pr_err("kvm-hv: failed to allocated nested partition table\n");
		return -ENOMEM;
	}

	ptcr = __pa(pseries_partition_tb) | (ptb_order - 8);
	rc = plpar_hcall_norets(H_SET_PARTITION_TABLE, ptcr);
	if (rc != H_SUCCESS) {
		pr_err("kvm-hv: Parent hypervisor does not support nesting (rc=%ld)\n",
		       rc);
		kfree(pseries_partition_tb);
		pseries_partition_tb = NULL;
		return -ENODEV;
	}

	return 0;
}