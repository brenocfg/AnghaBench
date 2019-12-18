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
struct mem_ctl_info {struct i5400_pvt* pvt_info; } ;
struct i5400_pvt {int /*<<< orphan*/  branchmap_werrors; int /*<<< orphan*/  fsb_error_regs; int /*<<< orphan*/  branch_0; int /*<<< orphan*/  branch_1; } ;

/* Variables and functions */
 int /*<<< orphan*/  pci_dev_put (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void i5400_put_devices(struct mem_ctl_info *mci)
{
	struct i5400_pvt *pvt;

	pvt = mci->pvt_info;

	/* Decrement usage count for devices */
	pci_dev_put(pvt->branch_1);
	pci_dev_put(pvt->branch_0);
	pci_dev_put(pvt->fsb_error_regs);
	pci_dev_put(pvt->branchmap_werrors);
}