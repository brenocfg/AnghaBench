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
typedef  scalar_t__ uint16_t ;

/* Variables and functions */
 scalar_t__ FSL_E500mc ; 
 scalar_t__ FSL_E5500 ; 
 scalar_t__ FSL_E6500 ; 
 int mfpvr () ; 

int
mpc85xx_is_qoriq(void)
{
	uint16_t pvr = mfpvr() >> 16;

	/* QorIQ register set is only in e500mc and derivative core based SoCs. */
	if (pvr == FSL_E500mc || pvr == FSL_E5500 || pvr == FSL_E6500)
		return (1);

	return (0);
}