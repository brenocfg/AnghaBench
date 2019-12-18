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

/* Variables and functions */
 int RBTX4938_IRQ_IOC ; 
 int __fls8 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rbtx4938_imstat_addr ; 
 int /*<<< orphan*/  readb (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int toshiba_rbtx4938_irq_nested(int sw_irq)
{
	u8 level3;

	level3 = readb(rbtx4938_imstat_addr);
	if (unlikely(!level3))
		return -1;
	/* must use fls so onboard ATA has priority */
	return RBTX4938_IRQ_IOC + __fls8(level3);
}