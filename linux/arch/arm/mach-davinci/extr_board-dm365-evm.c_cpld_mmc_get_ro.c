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
 int BIT (int) ; 
 scalar_t__ CPLD_CARDSTAT ; 
 int ENXIO ; 
 int __raw_readb (scalar_t__) ; 
 scalar_t__ cpld ; 

__attribute__((used)) static int cpld_mmc_get_ro(int module)
{
	if (!cpld)
		return -ENXIO;

	/* high == card's write protect switch active */
	return !!(__raw_readb(cpld + CPLD_CARDSTAT) & BIT(module ? 5 : 1));
}