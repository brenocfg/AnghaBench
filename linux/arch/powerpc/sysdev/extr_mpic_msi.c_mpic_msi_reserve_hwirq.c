#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  bitmap; } ;
struct mpic {TYPE_1__ msi_bitmap; } ;
typedef  int /*<<< orphan*/  irq_hw_number_t ;

/* Variables and functions */
 int /*<<< orphan*/  msi_bitmap_reserve_hwirq (TYPE_1__*,int /*<<< orphan*/ ) ; 

void mpic_msi_reserve_hwirq(struct mpic *mpic, irq_hw_number_t hwirq)
{
	/* The mpic calls this even when there is no allocator setup */
	if (!mpic->msi_bitmap.bitmap)
		return;

	msi_bitmap_reserve_hwirq(&mpic->msi_bitmap, hwirq);
}