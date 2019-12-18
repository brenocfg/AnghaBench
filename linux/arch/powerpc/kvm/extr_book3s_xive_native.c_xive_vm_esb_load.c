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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u64 ;
typedef  int u32 ;
struct xive_irq_data {int flags; scalar_t__ eoi_mmio; } ;

/* Variables and functions */
 int XIVE_IRQ_FLAG_SHIFT_BUG ; 
 int /*<<< orphan*/  in_be64 (scalar_t__) ; 

__attribute__((used)) static u8 xive_vm_esb_load(struct xive_irq_data *xd, u32 offset)
{
	u64 val;

	if (xd->flags & XIVE_IRQ_FLAG_SHIFT_BUG)
		offset |= offset << 4;

	val = in_be64(xd->eoi_mmio + offset);
	return (u8)val;
}