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
 int L2_CACHE_ALIGN_CNT (unsigned int) ; 
 unsigned int L2_CACHE_ALIGN_LOW (unsigned int) ; 
 int /*<<< orphan*/  cache_block_operation_wait (unsigned int) ; 
 int /*<<< orphan*/  cache_lock ; 
 int /*<<< orphan*/  imcr_get (unsigned int) ; 
 int /*<<< orphan*/  imcr_set (unsigned int,unsigned int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cache_block_operation(unsigned int *start,
				  unsigned int *end,
				  unsigned int bar_reg,
				  unsigned int wc_reg)
{
	unsigned long flags;
	unsigned int wcnt =
		(L2_CACHE_ALIGN_CNT((unsigned int) end)
		 - L2_CACHE_ALIGN_LOW((unsigned int) start)) >> 2;
	unsigned int wc = 0;

	for (; wcnt; wcnt -= wc, start += wc) {
loop:
		spin_lock_irqsave(&cache_lock, flags);

		/*
		 * If another cache operation is occurring
		 */
		if (unlikely(imcr_get(wc_reg))) {
			spin_unlock_irqrestore(&cache_lock, flags);

			/* Wait for previous operation completion */
			cache_block_operation_wait(wc_reg);

			/* Try again */
			goto loop;
		}

		imcr_set(bar_reg, L2_CACHE_ALIGN_LOW((unsigned int) start));

		if (wcnt > 0xffff)
			wc = 0xffff;
		else
			wc = wcnt;

		/* Set word count value in the WC register */
		imcr_set(wc_reg, wc & 0xffff);

		spin_unlock_irqrestore(&cache_lock, flags);

		/* Wait for completion */
		cache_block_operation_wait(wc_reg);
	}
}