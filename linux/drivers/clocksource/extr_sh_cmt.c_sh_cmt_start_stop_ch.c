#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct sh_cmt_channel {int timer_bit; TYPE_1__* cmt; } ;
struct TYPE_2__ {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  raw_spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  raw_spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int sh_cmt_read_cmstr (struct sh_cmt_channel*) ; 
 int /*<<< orphan*/  sh_cmt_write_cmstr (struct sh_cmt_channel*,int) ; 

__attribute__((used)) static void sh_cmt_start_stop_ch(struct sh_cmt_channel *ch, int start)
{
	unsigned long flags;
	u32 value;

	/* start stop register shared by multiple timer channels */
	raw_spin_lock_irqsave(&ch->cmt->lock, flags);
	value = sh_cmt_read_cmstr(ch);

	if (start)
		value |= 1 << ch->timer_bit;
	else
		value &= ~(1 << ch->timer_bit);

	sh_cmt_write_cmstr(ch, value);
	raw_spin_unlock_irqrestore(&ch->cmt->lock, flags);
}