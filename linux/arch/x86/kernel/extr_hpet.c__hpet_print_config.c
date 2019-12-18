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

/* Variables and functions */
 scalar_t__ HPET_CFG ; 
 scalar_t__ HPET_COUNTER ; 
 scalar_t__ HPET_ID ; 
 int HPET_ID_NUMBER ; 
 int HPET_ID_NUMBER_SHIFT ; 
 scalar_t__ HPET_PERIOD ; 
 scalar_t__ HPET_STATUS ; 
 scalar_t__ HPET_Tn_CFG (int) ; 
 scalar_t__ HPET_Tn_CMP (int) ; 
 scalar_t__ HPET_Tn_ROUTE (int) ; 
 int hpet_readl (scalar_t__) ; 
 int /*<<< orphan*/  pr_info (char*,...) ; 

__attribute__((used)) static void _hpet_print_config(const char *function, int line)
{
	u32 i, id, period, cfg, status, channels, l, h;

	pr_info("%s(%d):\n", function, line);

	id = hpet_readl(HPET_ID);
	period = hpet_readl(HPET_PERIOD);
	pr_info("ID: 0x%x, PERIOD: 0x%x\n", id, period);

	cfg = hpet_readl(HPET_CFG);
	status = hpet_readl(HPET_STATUS);
	pr_info("CFG: 0x%x, STATUS: 0x%x\n", cfg, status);

	l = hpet_readl(HPET_COUNTER);
	h = hpet_readl(HPET_COUNTER+4);
	pr_info("COUNTER_l: 0x%x, COUNTER_h: 0x%x\n", l, h);

	channels = ((id & HPET_ID_NUMBER) >> HPET_ID_NUMBER_SHIFT) + 1;

	for (i = 0; i < channels; i++) {
		l = hpet_readl(HPET_Tn_CFG(i));
		h = hpet_readl(HPET_Tn_CFG(i)+4);
		pr_info("T%d: CFG_l: 0x%x, CFG_h: 0x%x\n", i, l, h);

		l = hpet_readl(HPET_Tn_CMP(i));
		h = hpet_readl(HPET_Tn_CMP(i)+4);
		pr_info("T%d: CMP_l: 0x%x, CMP_h: 0x%x\n", i, l, h);

		l = hpet_readl(HPET_Tn_ROUTE(i));
		h = hpet_readl(HPET_Tn_ROUTE(i)+4);
		pr_info("T%d ROUTE_l: 0x%x, ROUTE_h: 0x%x\n", i, l, h);
	}
}