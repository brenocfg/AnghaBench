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
typedef  unsigned int u8 ;

/* Variables and functions */
 unsigned int const BIT (unsigned int) ; 

int ieee802_11_ext_capab(const u8 *ie, unsigned int capab)
{
	if (!ie || ie[1] <= capab / 8)
		return 0;
	return !!(ie[2 + capab / 8] & BIT(capab % 8));
}