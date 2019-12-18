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
typedef  int u8 ;

/* Variables and functions */
 scalar_t__ os_get_random (int*,int) ; 

int random_mac_addr_keep_oui(u8 *addr)
{
	if (os_get_random(addr + 3, 3) < 0)
		return -1;
	addr[0] &= 0xfe; /* unicast */
	addr[0] |= 0x02; /* locally administered */
	return 0;
}