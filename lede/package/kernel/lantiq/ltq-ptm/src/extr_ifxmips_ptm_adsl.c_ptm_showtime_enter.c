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
struct port_cell_info {int dummy; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * g_net_dev ; 
 int g_showtime ; 
 int /*<<< orphan*/  netif_carrier_on (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printk (char*) ; 

__attribute__((used)) static int ptm_showtime_enter(struct port_cell_info *port_cell, void *xdata_addr)
{
    int i;

    g_showtime = 1;

    for ( i = 0; i < ARRAY_SIZE(g_net_dev); i++ )
        netif_carrier_on(g_net_dev[i]);

    printk("enter showtime\n");

    return 0;
}