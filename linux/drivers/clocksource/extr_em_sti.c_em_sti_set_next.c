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
typedef  int u64 ;
struct em_sti_priv {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  STI_COMPA_H ; 
 int /*<<< orphan*/  STI_COMPA_L ; 
 int /*<<< orphan*/  STI_INTENCLR ; 
 int /*<<< orphan*/  STI_INTENSET ; 
 int /*<<< orphan*/  STI_INTFFCLR ; 
 int /*<<< orphan*/  em_sti_write (struct em_sti_priv*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  raw_spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  raw_spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static u64 em_sti_set_next(struct em_sti_priv *p, u64 next)
{
	unsigned long flags;

	raw_spin_lock_irqsave(&p->lock, flags);

	/* mask compare A interrupt */
	em_sti_write(p, STI_INTENCLR, 1);

	/* update compare A value */
	em_sti_write(p, STI_COMPA_H, next >> 32);
	em_sti_write(p, STI_COMPA_L, next & 0xffffffff);

	/* clear compare A interrupt source */
	em_sti_write(p, STI_INTFFCLR, 1);

	/* unmask compare A interrupt */
	em_sti_write(p, STI_INTENSET, 1);

	raw_spin_unlock_irqrestore(&p->lock, flags);

	return next;
}