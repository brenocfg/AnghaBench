#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  (* event_handler ) (TYPE_3__*) ;} ;
struct sh_cmt_channel {int flags; scalar_t__ match_value; scalar_t__ next_match_value; scalar_t__ max_match_value; TYPE_3__ ced; int /*<<< orphan*/  total_cycles; TYPE_2__* cmt; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_7__ {TYPE_1__* info; } ;
struct TYPE_6__ {int clear_bits; } ;

/* Variables and functions */
 int FLAG_CLOCKEVENT ; 
 int FLAG_CLOCKSOURCE ; 
 int FLAG_IRQCONTEXT ; 
 int FLAG_REPROGRAM ; 
 int FLAG_SKIPEVENT ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 scalar_t__ clockevent_state_oneshot (TYPE_3__*) ; 
 scalar_t__ clockevent_state_shutdown (TYPE_3__*) ; 
 int /*<<< orphan*/  sh_cmt_clock_event_program_verify (struct sh_cmt_channel*,int) ; 
 int sh_cmt_read_cmcsr (struct sh_cmt_channel*) ; 
 int /*<<< orphan*/  sh_cmt_write_cmcsr (struct sh_cmt_channel*,int) ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*) ; 

__attribute__((used)) static irqreturn_t sh_cmt_interrupt(int irq, void *dev_id)
{
	struct sh_cmt_channel *ch = dev_id;

	/* clear flags */
	sh_cmt_write_cmcsr(ch, sh_cmt_read_cmcsr(ch) &
			   ch->cmt->info->clear_bits);

	/* update clock source counter to begin with if enabled
	 * the wrap flag should be cleared by the timer specific
	 * isr before we end up here.
	 */
	if (ch->flags & FLAG_CLOCKSOURCE)
		ch->total_cycles += ch->match_value + 1;

	if (!(ch->flags & FLAG_REPROGRAM))
		ch->next_match_value = ch->max_match_value;

	ch->flags |= FLAG_IRQCONTEXT;

	if (ch->flags & FLAG_CLOCKEVENT) {
		if (!(ch->flags & FLAG_SKIPEVENT)) {
			if (clockevent_state_oneshot(&ch->ced)) {
				ch->next_match_value = ch->max_match_value;
				ch->flags |= FLAG_REPROGRAM;
			}

			ch->ced.event_handler(&ch->ced);
		}
	}

	ch->flags &= ~FLAG_SKIPEVENT;

	if (ch->flags & FLAG_REPROGRAM) {
		ch->flags &= ~FLAG_REPROGRAM;
		sh_cmt_clock_event_program_verify(ch, 1);

		if (ch->flags & FLAG_CLOCKEVENT)
			if ((clockevent_state_shutdown(&ch->ced))
			    || (ch->match_value == ch->next_match_value))
				ch->flags &= ~FLAG_REPROGRAM;
	}

	ch->flags &= ~FLAG_IRQCONTEXT;

	return IRQ_HANDLED;
}