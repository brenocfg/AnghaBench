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
typedef  int u32 ;
struct TYPE_2__ {int /*<<< orphan*/  dout; } ;

/* Variables and functions */
 int __raw_readl (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __raw_writel (int,int /*<<< orphan*/ *) ; 
 TYPE_1__* txx9_pioptr ; 

__attribute__((used)) static void txx9_gpio_set_raw(unsigned int offset, int value)
{
	u32 val;
	val = __raw_readl(&txx9_pioptr->dout);
	if (value)
		val |= 1 << offset;
	else
		val &= ~(1 << offset);
	__raw_writel(val, &txx9_pioptr->dout);
}