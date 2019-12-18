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
 unsigned int mips_hpt_frequency ; 

__attribute__((used)) static int htp_freq_to_cpu_freq(unsigned int clk_mult)
{
	return mips_hpt_frequency * clk_mult / 1000;
}