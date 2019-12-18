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
 unsigned int octeon_irq_ciu3_base_mbox_intsn (int) ; 

__attribute__((used)) static unsigned int octeon_irq_ciu3_mbox_intsn_for_core(int core, unsigned int mbox)
{
	return octeon_irq_ciu3_base_mbox_intsn(core) + mbox;
}