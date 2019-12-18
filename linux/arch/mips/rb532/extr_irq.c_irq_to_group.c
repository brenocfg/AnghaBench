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
 unsigned int GROUP0_IRQ_BASE ; 

__attribute__((used)) static inline int irq_to_group(unsigned int irq_nr)
{
	return (irq_nr - GROUP0_IRQ_BASE) >> 5;
}