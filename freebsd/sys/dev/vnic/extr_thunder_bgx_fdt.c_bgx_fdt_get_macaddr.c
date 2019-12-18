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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  phandle_t ;

/* Variables and functions */
 int ETHER_ADDR_LEN ; 
 int OF_getprop (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
bgx_fdt_get_macaddr(phandle_t phy, uint8_t *hwaddr)
{
	uint8_t addr[ETHER_ADDR_LEN];

	if (OF_getprop(phy, "local-mac-address", addr, ETHER_ADDR_LEN) == -1) {
		/* Missing MAC address should be marked by clearing it */
		memset(hwaddr, 0, ETHER_ADDR_LEN);
	} else
		memcpy(hwaddr, addr, ETHER_ADDR_LEN);
}