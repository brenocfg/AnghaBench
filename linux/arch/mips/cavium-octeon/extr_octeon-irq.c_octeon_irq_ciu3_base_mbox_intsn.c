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
 int CIU3_MBOX_PER_CORE ; 

__attribute__((used)) static unsigned int octeon_irq_ciu3_base_mbox_intsn(int core)
{
	/* SW (mbox) are 0x04 in bits 12..19 */
	return 0x04000 + CIU3_MBOX_PER_CORE * core;
}