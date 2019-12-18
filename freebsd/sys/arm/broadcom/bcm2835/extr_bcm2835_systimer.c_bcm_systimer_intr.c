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
typedef  int uint32_t ;
struct TYPE_2__ {int /*<<< orphan*/  et_arg; int /*<<< orphan*/  (* et_event_cb ) (TYPE_1__*,int /*<<< orphan*/ ) ;scalar_t__ et_active; } ;
struct systimer {int index; TYPE_1__ et; scalar_t__ enabled; } ;

/* Variables and functions */
 int FILTER_HANDLED ; 
 int FILTER_STRAY ; 
 int /*<<< orphan*/  SYSTIMER_CS ; 
 int bcm_systimer_tc_read_4 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcm_systimer_tc_write_4 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
bcm_systimer_intr(void *arg)
{
	struct systimer *st = (struct systimer *)arg;
	uint32_t cs;

	cs = bcm_systimer_tc_read_4(SYSTIMER_CS);
	if ((cs & (1 << st->index)) == 0)
		return (FILTER_STRAY);

	/* ACK interrupt */
	bcm_systimer_tc_write_4(SYSTIMER_CS, (1 << st->index));
	if (st->enabled) {
		if (st->et.et_active) {
			st->et.et_event_cb(&st->et, st->et.et_arg);
		}
	}

	return (FILTER_HANDLED);
}