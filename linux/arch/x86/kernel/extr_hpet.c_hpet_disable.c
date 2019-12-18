#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_4__ {int boot_cfg; unsigned int nr_channels; TYPE_1__* channels; } ;
struct TYPE_3__ {int boot_cfg; } ;

/* Variables and functions */
 int /*<<< orphan*/  HPET_CFG ; 
 int HPET_CFG_ENABLE ; 
 int /*<<< orphan*/  HPET_Tn_CFG (unsigned int) ; 
 TYPE_2__ hpet_base ; 
 int /*<<< orphan*/  hpet_virt_address ; 
 int /*<<< orphan*/  hpet_writel (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_hpet_capable () ; 

void hpet_disable(void)
{
	unsigned int i;
	u32 cfg;

	if (!is_hpet_capable() || !hpet_virt_address)
		return;

	/* Restore boot configuration with the enable bit cleared */
	cfg = hpet_base.boot_cfg;
	cfg &= ~HPET_CFG_ENABLE;
	hpet_writel(cfg, HPET_CFG);

	/* Restore the channel boot configuration */
	for (i = 0; i < hpet_base.nr_channels; i++)
		hpet_writel(hpet_base.channels[i].boot_cfg, HPET_Tn_CFG(i));

	/* If the HPET was enabled at boot time, reenable it */
	if (hpet_base.boot_cfg & HPET_CFG_ENABLE)
		hpet_writel(hpet_base.boot_cfg, HPET_CFG);
}