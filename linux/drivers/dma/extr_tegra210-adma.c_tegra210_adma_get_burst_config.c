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
 unsigned int ADMA_CH_CONFIG_BURST_SIZE_SHIFT ; 
 unsigned int ADMA_CH_CONFIG_MAX_BURST_SIZE ; 
 unsigned int fls (unsigned int) ; 

__attribute__((used)) static unsigned int tegra210_adma_get_burst_config(unsigned int burst_size)
{
	if (!burst_size || burst_size > ADMA_CH_CONFIG_MAX_BURST_SIZE)
		burst_size = ADMA_CH_CONFIG_MAX_BURST_SIZE;

	return fls(burst_size) << ADMA_CH_CONFIG_BURST_SIZE_SHIFT;
}