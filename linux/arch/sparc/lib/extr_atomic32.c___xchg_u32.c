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
typedef  scalar_t__ volatile u32 ;

/* Variables and functions */
 int /*<<< orphan*/  ATOMIC_HASH (scalar_t__ volatile*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ ,unsigned long) ; 

unsigned long __xchg_u32(volatile u32 *ptr, u32 new)
{
	unsigned long flags;
	u32 prev;

	spin_lock_irqsave(ATOMIC_HASH(ptr), flags);
	prev = *ptr;
	*ptr = new;
	spin_unlock_irqrestore(ATOMIC_HASH(ptr), flags);

	return (unsigned long)prev;
}