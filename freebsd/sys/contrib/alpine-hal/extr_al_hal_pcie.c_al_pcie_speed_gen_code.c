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
typedef  enum al_pcie_link_speed { ____Placeholder_al_pcie_link_speed } al_pcie_link_speed ;

/* Variables and functions */
 int AL_PCIE_LINK_SPEED_GEN1 ; 
 int AL_PCIE_LINK_SPEED_GEN2 ; 
 int AL_PCIE_LINK_SPEED_GEN3 ; 

__attribute__((used)) static unsigned int
al_pcie_speed_gen_code(enum al_pcie_link_speed speed)
{
	if (speed == AL_PCIE_LINK_SPEED_GEN1)
		return 1;
	if (speed == AL_PCIE_LINK_SPEED_GEN2)
		return 2;
	if (speed == AL_PCIE_LINK_SPEED_GEN3)
		return 3;
	/* must not be reached */
	return 0;
}