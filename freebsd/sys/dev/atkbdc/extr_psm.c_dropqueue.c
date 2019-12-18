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
struct TYPE_2__ {scalar_t__ tail; scalar_t__ head; scalar_t__ count; } ;
struct psm_softc {int state; int /*<<< orphan*/  pqueue_end; int /*<<< orphan*/  pqueue_start; int /*<<< orphan*/  softcallout; TYPE_1__ queue; } ;

/* Variables and functions */
 int PSM_SOFTARMED ; 
 int /*<<< orphan*/  callout_stop (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
dropqueue(struct psm_softc *sc)
{

	sc->queue.count = 0;
	sc->queue.head = 0;
	sc->queue.tail = 0;
	if ((sc->state & PSM_SOFTARMED) != 0) {
		sc->state &= ~PSM_SOFTARMED;
		callout_stop(&sc->softcallout);
	}
	sc->pqueue_start = sc->pqueue_end;
}