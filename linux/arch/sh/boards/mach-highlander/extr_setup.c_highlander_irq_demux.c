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
 int HL_NR_IRL ; 
 int* irl2irq ; 

__attribute__((used)) static int highlander_irq_demux(int irq)
{
	if (irq >= HL_NR_IRL || irq < 0 || !irl2irq[irq])
		return irq;

	return irl2irq[irq];
}