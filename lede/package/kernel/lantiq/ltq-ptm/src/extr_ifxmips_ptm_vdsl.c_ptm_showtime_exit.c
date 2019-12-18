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
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IFX_REG_W32 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UTP_CFG ; 
 int /*<<< orphan*/ * g_net_dev ; 
 scalar_t__ g_showtime ; 
 int /*<<< orphan*/ * g_xdata_addr ; 
 int /*<<< orphan*/  netif_carrier_off (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printk (char*) ; 

__attribute__((used)) static int ptm_showtime_exit(void)
{
	int i;

	if ( !g_showtime )
		return -1;

	//#ifdef CONFIG_VR9
	//    IFX_REG_W32_MASK(0, 1 << 17, FFSM_CFG0);
	//#endif

	IFX_REG_W32(0x00, UTP_CFG);

	for ( i = 0; i < ARRAY_SIZE(g_net_dev); i++ )
		netif_carrier_off(g_net_dev[i]);

	g_showtime = 0;

	//  TODO: ReTX clean state
	g_xdata_addr = NULL;

	printk("leave showtime\n");

	return 0;
}