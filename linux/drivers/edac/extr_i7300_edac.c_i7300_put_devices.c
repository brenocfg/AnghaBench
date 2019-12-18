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
struct mem_ctl_info {struct i7300_pvt* pvt_info; } ;
struct i7300_pvt {int /*<<< orphan*/  pci_dev_16_1_fsb_addr_map; int /*<<< orphan*/  pci_dev_16_2_fsb_err_regs; int /*<<< orphan*/ * pci_dev_2x_0_fbd_branch; } ;

/* Variables and functions */
 int MAX_CH_PER_BRANCH ; 
 int /*<<< orphan*/  pci_dev_put (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void i7300_put_devices(struct mem_ctl_info *mci)
{
	struct i7300_pvt *pvt;
	int branch;

	pvt = mci->pvt_info;

	/* Decrement usage count for devices */
	for (branch = 0; branch < MAX_CH_PER_BRANCH; branch++)
		pci_dev_put(pvt->pci_dev_2x_0_fbd_branch[branch]);
	pci_dev_put(pvt->pci_dev_16_2_fsb_err_regs);
	pci_dev_put(pvt->pci_dev_16_1_fsb_addr_map);
}