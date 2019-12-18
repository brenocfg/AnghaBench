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
typedef  unsigned int u32 ;

/* Variables and functions */
 unsigned int IRQ_EINT (unsigned int) ; 
 int /*<<< orphan*/  S3C64XX_EINT0MASK ; 
 int /*<<< orphan*/  S3C64XX_EINT0PEND ; 
 unsigned int __raw_readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  generic_handle_irq (unsigned int) ; 

__attribute__((used)) static inline void s3c_irq_demux_eint(unsigned int start, unsigned int end)
{
	u32 status = __raw_readl(S3C64XX_EINT0PEND);
	u32 mask = __raw_readl(S3C64XX_EINT0MASK);
	unsigned int irq;

	status &= ~mask;
	status >>= start;
	status &= (1 << (end - start + 1)) - 1;

	for (irq = IRQ_EINT(start); irq <= IRQ_EINT(end); irq++) {
		if (status & 1)
			generic_handle_irq(irq);

		status >>= 1;
	}
}