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
 unsigned int CP0_ERRCTL_DCACHE ; 
 unsigned int CP0_ERRCTL_ICACHE ; 
 unsigned int CP0_ERRCTL_MULTIBUS ; 
 unsigned int CP0_ERRCTL_RECOVERABLE ; 
 int /*<<< orphan*/  printk (char*) ; 

__attribute__((used)) static inline void breakout_errctl(unsigned int val)
{
	if (val & CP0_ERRCTL_RECOVERABLE)
		printk(" recoverable");
	if (val & CP0_ERRCTL_DCACHE)
		printk(" dcache");
	if (val & CP0_ERRCTL_ICACHE)
		printk(" icache");
	if (val & CP0_ERRCTL_MULTIBUS)
		printk(" multiple-buserr");
	printk("\n");
}