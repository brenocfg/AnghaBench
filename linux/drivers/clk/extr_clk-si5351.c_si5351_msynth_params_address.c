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
typedef  scalar_t__ u8 ;

/* Variables and functions */
 scalar_t__ SI5351_CLK0_PARAMETERS ; 
 scalar_t__ SI5351_CLK6_PARAMETERS ; 
 int SI5351_PARAMETERS_LENGTH ; 

__attribute__((used)) static inline u8 si5351_msynth_params_address(int num)
{
	if (num > 5)
		return SI5351_CLK6_PARAMETERS + (num - 6);
	return SI5351_CLK0_PARAMETERS + (SI5351_PARAMETERS_LENGTH * num);
}