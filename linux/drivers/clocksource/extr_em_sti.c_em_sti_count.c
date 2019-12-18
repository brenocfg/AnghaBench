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
 int /*<<< orphan*/  STI_COUNT_H ; 
 int /*<<< orphan*/  STI_COUNT_L ; 
 int em_sti_read (struct em_sti_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  raw_spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  raw_spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static u64 em_sti_count(struct em_sti_priv *p)
{
	u64 ticks;
	unsigned long flags;

	/* the STI hardware buffers the 48-bit count, but to
	 * break it out into two 32-bit access the registers
	 * must be accessed in a certain order.
	 * Always read STI_COUNT_H before STI_COUNT_L.
	 */
	raw_spin_lock_irqsave(&p->lock, flags);
	ticks = (u64)(em_sti_read(p, STI_COUNT_H) & 0xffff) << 32;
	ticks |= em_sti_read(p, STI_COUNT_L);
	raw_spin_unlock_irqrestore(&p->lock, flags);

	return ticks;
}