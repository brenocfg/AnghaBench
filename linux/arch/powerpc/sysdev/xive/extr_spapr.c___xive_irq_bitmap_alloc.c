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
struct xive_irq_bitmap {int count; scalar_t__ base; int /*<<< orphan*/  bitmap; } ;

/* Variables and functions */
 int ENOMEM ; 
 int find_first_zero_bit (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  set_bit (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int __xive_irq_bitmap_alloc(struct xive_irq_bitmap *xibm)
{
	int irq;

	irq = find_first_zero_bit(xibm->bitmap, xibm->count);
	if (irq != xibm->count) {
		set_bit(irq, xibm->bitmap);
		irq += xibm->base;
	} else {
		irq = -ENOMEM;
	}

	return irq;
}