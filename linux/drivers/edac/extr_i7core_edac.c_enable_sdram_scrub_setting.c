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
typedef  int u32 ;
struct mem_ctl_info {int /*<<< orphan*/  get_sdram_scrub_rate; int /*<<< orphan*/  set_sdram_scrub_rate; struct i7core_pvt* pvt_info; } ;
struct i7core_pvt {int /*<<< orphan*/  pci_noncore; } ;

/* Variables and functions */
 int /*<<< orphan*/  MC_CFG_CONTROL ; 
 int MC_CFG_UNLOCK ; 
 int /*<<< orphan*/  get_sdram_scrub_rate ; 
 int /*<<< orphan*/  pci_read_config_dword (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  pci_write_config_dword (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  set_sdram_scrub_rate ; 

__attribute__((used)) static void enable_sdram_scrub_setting(struct mem_ctl_info *mci)
{
	struct i7core_pvt *pvt = mci->pvt_info;
	u32 pci_lock;

	/* Unlock writes to pci registers */
	pci_read_config_dword(pvt->pci_noncore, MC_CFG_CONTROL, &pci_lock);
	pci_lock &= ~0x3;
	pci_write_config_dword(pvt->pci_noncore, MC_CFG_CONTROL,
			       pci_lock | MC_CFG_UNLOCK);

	mci->set_sdram_scrub_rate = set_sdram_scrub_rate;
	mci->get_sdram_scrub_rate = get_sdram_scrub_rate;
}