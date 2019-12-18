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
struct TYPE_3__ {int flags; int /*<<< orphan*/  cxgb_tick_ch; int /*<<< orphan*/  tick_task; int /*<<< orphan*/  tq; } ;
typedef  TYPE_1__ adapter_t ;

/* Variables and functions */
 int CXGB_SHUTDOWN ; 
 int /*<<< orphan*/  callout_reset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void (*) (void*),TYPE_1__*) ; 
 int /*<<< orphan*/  hz ; 
 int /*<<< orphan*/  taskqueue_enqueue (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
cxgb_tick(void *arg)
{
	adapter_t *sc = (adapter_t *)arg;

	if (sc->flags & CXGB_SHUTDOWN)
		return;

	taskqueue_enqueue(sc->tq, &sc->tick_task);	
	callout_reset(&sc->cxgb_tick_ch, hz, cxgb_tick, sc);
}