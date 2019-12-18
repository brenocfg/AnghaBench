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
 int /*<<< orphan*/  outb (unsigned long,int) ; 

__attribute__((used)) static inline void
cabriolet_update_irq_hw(unsigned int irq, unsigned long mask)
{
	int ofs = (irq - 16) / 8;
	outb(mask >> (16 + ofs * 8), 0x804 + ofs);
}