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
 int /*<<< orphan*/  __wd_smp_lock ; 
 int /*<<< orphan*/  hard_irq_disable () ; 
 int /*<<< orphan*/  raw_local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  raw_local_irq_save (unsigned long) ; 
 int /*<<< orphan*/  spin_until_cond (int) ; 
 int /*<<< orphan*/  test_and_set_bit_lock (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void wd_smp_lock(unsigned long *flags)
{
	/*
	 * Avoid locking layers if possible.
	 * This may be called from low level interrupt handlers at some
	 * point in future.
	 */
	raw_local_irq_save(*flags);
	hard_irq_disable(); /* Make it soft-NMI safe */
	while (unlikely(test_and_set_bit_lock(0, &__wd_smp_lock))) {
		raw_local_irq_restore(*flags);
		spin_until_cond(!test_bit(0, &__wd_smp_lock));
		raw_local_irq_save(*flags);
		hard_irq_disable();
	}
}