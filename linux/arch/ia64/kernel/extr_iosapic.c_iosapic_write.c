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
typedef  int /*<<< orphan*/  u32 ;
struct iosapic {int /*<<< orphan*/  lock; int /*<<< orphan*/  addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  __iosapic_write (int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static inline void
iosapic_write(struct iosapic *iosapic, unsigned int reg, u32 val)
{
	unsigned long flags;

	spin_lock_irqsave(&iosapic->lock, flags);
	__iosapic_write(iosapic->addr, reg, val);
	spin_unlock_irqrestore(&iosapic->lock, flags);
}