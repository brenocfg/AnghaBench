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
typedef  int /*<<< orphan*/  volatile u64 ;

/* Variables and functions */
 int /*<<< orphan*/  _atomic_spin_lock_irqsave (int /*<<< orphan*/  volatile*,unsigned long) ; 
 int /*<<< orphan*/  _atomic_spin_unlock_irqrestore (int /*<<< orphan*/  volatile*,unsigned long) ; 

u64 __cmpxchg_u64(volatile u64 *ptr, u64 old, u64 new)
{
	unsigned long flags;
	u64 prev;

	_atomic_spin_lock_irqsave(ptr, flags);
	if ((prev = *ptr) == old)
		*ptr = new;
	_atomic_spin_unlock_irqrestore(ptr, flags);
	return prev;
}