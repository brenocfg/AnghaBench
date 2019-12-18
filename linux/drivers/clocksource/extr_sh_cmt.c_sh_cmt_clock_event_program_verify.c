#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct sh_cmt_channel {int next_match_value; int max_match_value; int match_value; int /*<<< orphan*/  index; TYPE_2__* cmt; int /*<<< orphan*/  flags; } ;
struct TYPE_4__ {TYPE_1__* pdev; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  FLAG_REPROGRAM ; 
 int /*<<< orphan*/  FLAG_SKIPEVENT ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int sh_cmt_get_counter (struct sh_cmt_channel*,int*) ; 
 int /*<<< orphan*/  sh_cmt_write_cmcor (struct sh_cmt_channel*,int) ; 

__attribute__((used)) static void sh_cmt_clock_event_program_verify(struct sh_cmt_channel *ch,
					      int absolute)
{
	u32 value = ch->next_match_value;
	u32 new_match;
	u32 delay = 0;
	u32 now = 0;
	u32 has_wrapped;

	now = sh_cmt_get_counter(ch, &has_wrapped);
	ch->flags |= FLAG_REPROGRAM; /* force reprogram */

	if (has_wrapped) {
		/* we're competing with the interrupt handler.
		 *  -> let the interrupt handler reprogram the timer.
		 *  -> interrupt number two handles the event.
		 */
		ch->flags |= FLAG_SKIPEVENT;
		return;
	}

	if (absolute)
		now = 0;

	do {
		/* reprogram the timer hardware,
		 * but don't save the new match value yet.
		 */
		new_match = now + value + delay;
		if (new_match > ch->max_match_value)
			new_match = ch->max_match_value;

		sh_cmt_write_cmcor(ch, new_match);

		now = sh_cmt_get_counter(ch, &has_wrapped);
		if (has_wrapped && (new_match > ch->match_value)) {
			/* we are changing to a greater match value,
			 * so this wrap must be caused by the counter
			 * matching the old value.
			 * -> first interrupt reprograms the timer.
			 * -> interrupt number two handles the event.
			 */
			ch->flags |= FLAG_SKIPEVENT;
			break;
		}

		if (has_wrapped) {
			/* we are changing to a smaller match value,
			 * so the wrap must be caused by the counter
			 * matching the new value.
			 * -> save programmed match value.
			 * -> let isr handle the event.
			 */
			ch->match_value = new_match;
			break;
		}

		/* be safe: verify hardware settings */
		if (now < new_match) {
			/* timer value is below match value, all good.
			 * this makes sure we won't miss any match events.
			 * -> save programmed match value.
			 * -> let isr handle the event.
			 */
			ch->match_value = new_match;
			break;
		}

		/* the counter has reached a value greater
		 * than our new match value. and since the
		 * has_wrapped flag isn't set we must have
		 * programmed a too close event.
		 * -> increase delay and retry.
		 */
		if (delay)
			delay <<= 1;
		else
			delay = 1;

		if (!delay)
			dev_warn(&ch->cmt->pdev->dev, "ch%u: too long delay\n",
				 ch->index);

	} while (delay);
}