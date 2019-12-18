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
struct mpic_reg_bank {int /*<<< orphan*/ * base; } ;
struct mpic {int dummy; } ;
typedef  scalar_t__ phys_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ioremap (scalar_t__,unsigned int) ; 

__attribute__((used)) static void _mpic_map_mmio(struct mpic *mpic, phys_addr_t phys_addr,
			   struct mpic_reg_bank *rb, unsigned int offset,
			   unsigned int size)
{
	rb->base = ioremap(phys_addr + offset, size);
	BUG_ON(rb->base == NULL);
}