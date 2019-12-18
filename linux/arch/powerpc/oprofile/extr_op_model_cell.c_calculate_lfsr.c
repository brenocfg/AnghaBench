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
 int ENTRIES ; 
 int V2_16 ; 
 int V2_19 ; 
 int V2_22 ; 
 int* initial_lfsr ; 

__attribute__((used)) static int calculate_lfsr(int n)
{
	/*
	 * The ranges and steps are in powers of 2 so the calculations
	 * can be done using shifts rather then divide.
	 */
	int index;

	if ((n >> 16) == 0)
		index = 0;
	else if (((n - V2_16) >> 19) == 0)
		index = ((n - V2_16) >> 12) + 1;
	else if (((n - V2_16 - V2_19) >> 22) == 0)
		index = ((n - V2_16 - V2_19) >> 15 ) + 1 + 128;
	else if (((n - V2_16 - V2_19 - V2_22) >> 24) == 0)
		index = ((n - V2_16 - V2_19 - V2_22) >> 18 ) + 1 + 256;
	else
		index = ENTRIES-1;

	/* make sure index is valid */
	if ((index >= ENTRIES) || (index < 0))
		index = ENTRIES-1;

	return initial_lfsr[index];
}