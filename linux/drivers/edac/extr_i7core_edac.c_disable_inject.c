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
struct mem_ctl_info {struct i7core_pvt* pvt_info; } ;
struct TYPE_2__ {size_t channel; scalar_t__ enable; } ;
struct i7core_pvt {TYPE_1__ inject; int /*<<< orphan*/ ** pci_ch; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  MC_CHANNEL_ERROR_INJECT ; 
 int /*<<< orphan*/  pci_write_config_dword (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int disable_inject(const struct mem_ctl_info *mci)
{
	struct i7core_pvt *pvt = mci->pvt_info;

	pvt->inject.enable = 0;

	if (!pvt->pci_ch[pvt->inject.channel][0])
		return -ENODEV;

	pci_write_config_dword(pvt->pci_ch[pvt->inject.channel][0],
				MC_CHANNEL_ERROR_INJECT, 0);

	return 0;
}