#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct trapframe {int dummy; } ;
struct decr_state {int mode; scalar_t__ div; } ;
typedef  scalar_t__ int32_t ;
struct TYPE_3__ {int /*<<< orphan*/  et_arg; int /*<<< orphan*/  (* et_event_cb ) (TYPE_1__*,int /*<<< orphan*/ ) ;scalar_t__ et_active; } ;

/* Variables and functions */
 struct decr_state* DPCPU_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SPR_TSR ; 
 int /*<<< orphan*/  TSR_DIS ; 
 size_t curcpu ; 
 int /*<<< orphan*/ ** decr_counts ; 
 TYPE_1__ decr_et ; 
 int /*<<< orphan*/  decr_et_stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  decr_state ; 
 int /*<<< orphan*/  initialized ; 
 int /*<<< orphan*/  mtdec (scalar_t__) ; 
 int /*<<< orphan*/  mtspr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,int /*<<< orphan*/ ) ; 

void
decr_intr(struct trapframe *frame)
{
	struct decr_state *s = DPCPU_PTR(decr_state);
	int		nticks = 0;
	int32_t		val;

	if (!initialized)
		return;

	(*decr_counts[curcpu])++;

#ifdef BOOKE
	/*
	 * Interrupt handler must reset DIS to avoid getting another
	 * interrupt once EE is enabled.
	 */
	mtspr(SPR_TSR, TSR_DIS);
#endif

	if (s->mode == 1) {
		/*
		 * Based on the actual time delay since the last decrementer
		 * reload, we arrange for earlier interrupt next time.
		 */
		__asm ("mfdec %0" : "=r"(val));
		while (val < 0) {
			val += s->div;
			nticks++;
		}
		mtdec(val);
	} else if (s->mode == 2) {
		nticks = 1;
		decr_et_stop(NULL);
	} else if (s->mode == 0) {
		/* Potemkin timer ran out without an event. Just reset it. */
		decr_et_stop(NULL);
	}

	while (nticks-- > 0) {
		if (decr_et.et_active)
			decr_et.et_event_cb(&decr_et, decr_et.et_arg);
	}
}