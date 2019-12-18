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
 int RBTX4939_IRQ_IOC ; 
 int __fls8 (unsigned char) ; 
 int /*<<< orphan*/  rbtx4939_ifac2_addr ; 
 unsigned char readb (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static inline int rbtx4939_ioc_irqroute(void)
{
	unsigned char istat = readb(rbtx4939_ifac2_addr);

	if (unlikely(istat == 0))
		return -1;
	return RBTX4939_IRQ_IOC + __fls8(istat);
}