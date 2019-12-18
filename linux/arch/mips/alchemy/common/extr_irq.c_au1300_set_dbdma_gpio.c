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
 scalar_t__ AU1300_GPIC_ADDR ; 
 scalar_t__ AU1300_GPIC_DMASEL ; 
 unsigned long __raw_readl (scalar_t__) ; 
 int /*<<< orphan*/  __raw_writel (unsigned long,scalar_t__) ; 
 int /*<<< orphan*/  wmb () ; 

void au1300_set_dbdma_gpio(int dchan, unsigned int gpio)
{
	unsigned long r;

	if ((dchan >= 0) && (dchan <= 1)) {
		r = __raw_readl(AU1300_GPIC_ADDR + AU1300_GPIC_DMASEL);
		r &= ~(0xff << (8 * dchan));
		r |= (gpio & 0x7f) << (8 * dchan);
		__raw_writel(r, AU1300_GPIC_ADDR + AU1300_GPIC_DMASEL);
		wmb();
	}
}