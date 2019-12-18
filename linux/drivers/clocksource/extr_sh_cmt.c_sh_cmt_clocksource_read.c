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
typedef  scalar_t__ u64 ;
typedef  scalar_t__ u32 ;
struct sh_cmt_channel {int /*<<< orphan*/  lock; scalar_t__ match_value; scalar_t__ total_cycles; } ;
struct clocksource {int dummy; } ;

/* Variables and functions */
 struct sh_cmt_channel* cs_to_sh_cmt (struct clocksource*) ; 
 int /*<<< orphan*/  raw_spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  raw_spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ sh_cmt_get_counter (struct sh_cmt_channel*,scalar_t__*) ; 
 scalar_t__ unlikely (scalar_t__) ; 

__attribute__((used)) static u64 sh_cmt_clocksource_read(struct clocksource *cs)
{
	struct sh_cmt_channel *ch = cs_to_sh_cmt(cs);
	unsigned long flags;
	u32 has_wrapped;
	u64 value;
	u32 raw;

	raw_spin_lock_irqsave(&ch->lock, flags);
	value = ch->total_cycles;
	raw = sh_cmt_get_counter(ch, &has_wrapped);

	if (unlikely(has_wrapped))
		raw += ch->match_value + 1;
	raw_spin_unlock_irqrestore(&ch->lock, flags);

	return value + raw;
}