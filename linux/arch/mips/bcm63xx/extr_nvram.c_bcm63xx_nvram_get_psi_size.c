#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ psi_size; } ;

/* Variables and functions */
 int BCM63XX_DEFAULT_PSI_SIZE ; 
 TYPE_1__ nvram ; 

int bcm63xx_nvram_get_psi_size(void)
{
	if (nvram.psi_size > 0)
		return nvram.psi_size;

	return BCM63XX_DEFAULT_PSI_SIZE;
}