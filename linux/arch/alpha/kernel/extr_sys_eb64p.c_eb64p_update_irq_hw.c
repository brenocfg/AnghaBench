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
eb64p_update_irq_hw(unsigned int irq, unsigned long mask)
{
	outb(mask >> (irq >= 24 ? 24 : 16), (irq >= 24 ? 0x27 : 0x26));
}