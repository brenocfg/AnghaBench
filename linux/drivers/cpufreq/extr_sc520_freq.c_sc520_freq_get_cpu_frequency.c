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
 int* cpuctl ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 

__attribute__((used)) static unsigned int sc520_freq_get_cpu_frequency(unsigned int cpu)
{
	u8 clockspeed_reg = *cpuctl;

	switch (clockspeed_reg & 0x03) {
	default:
		pr_err("error: cpuctl register has unexpected value %02x\n",
		       clockspeed_reg);
	case 0x01:
		return 100000;
	case 0x02:
		return 133000;
	}
}