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
struct sh_cmt_channel {unsigned long flags; int /*<<< orphan*/  lock; int /*<<< orphan*/  max_match_value; } ;

/* Variables and functions */
 unsigned long FLAG_CLOCKEVENT ; 
 unsigned long FLAG_CLOCKSOURCE ; 
 int /*<<< orphan*/  __sh_cmt_set_next (struct sh_cmt_channel*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  raw_spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  raw_spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int sh_cmt_enable (struct sh_cmt_channel*) ; 

__attribute__((used)) static int sh_cmt_start(struct sh_cmt_channel *ch, unsigned long flag)
{
	int ret = 0;
	unsigned long flags;

	raw_spin_lock_irqsave(&ch->lock, flags);

	if (!(ch->flags & (FLAG_CLOCKEVENT | FLAG_CLOCKSOURCE)))
		ret = sh_cmt_enable(ch);

	if (ret)
		goto out;
	ch->flags |= flag;

	/* setup timeout if no clockevent */
	if ((flag == FLAG_CLOCKSOURCE) && (!(ch->flags & FLAG_CLOCKEVENT)))
		__sh_cmt_set_next(ch, ch->max_match_value);
 out:
	raw_spin_unlock_irqrestore(&ch->lock, flags);

	return ret;
}