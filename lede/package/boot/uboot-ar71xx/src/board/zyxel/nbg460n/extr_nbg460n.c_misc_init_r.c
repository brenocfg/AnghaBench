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
typedef  int uint8_t ;

/* Variables and functions */
 scalar_t__ CONFIG_ETHADDR_ADDR ; 
 int /*<<< orphan*/  debug (char*,...) ; 
 int /*<<< orphan*/  eth_getenv_enetaddr (char*,int*) ; 
 int /*<<< orphan*/  eth_setenv_enetaddr (char*,int*) ; 
 int /*<<< orphan*/  memcpy (int*,int*,int) ; 

int misc_init_r(void) {
    uint8_t macaddr[6];
    uint8_t enetaddr[6];

	debug("Testing mac addresses\n");
	
    memcpy(macaddr, (uint8_t *) CONFIG_ETHADDR_ADDR, 6);

    if (!eth_getenv_enetaddr("ethaddr", enetaddr)) {
        debug("Setting eth0 mac addr to %pM\n", macaddr);
        eth_setenv_enetaddr("ethaddr", macaddr);
    }

    if (!eth_getenv_enetaddr("eth1addr", enetaddr)) {
		macaddr[5] += 1;
        debug("Setting eth1 mac addr to %pM\n", macaddr);
        eth_setenv_enetaddr("eth1addr", macaddr);
    }

    return 0;
}