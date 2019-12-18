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
 size_t ETH_ALEN ; 

__attribute__((used)) static int match_mac_mask(const u8 *addr_a, const u8 *addr_b, const u8 *mask)
{
	size_t i;

	for (i = 0; i < ETH_ALEN; i++) {
		if ((addr_a[i] & mask[i]) != (addr_b[i] & mask[i]))
			return 0;
	}
	return 1;
}