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
struct vtcon_softc {int /*<<< orphan*/  vtcon_ctrl_task; } ;

/* Variables and functions */
 int /*<<< orphan*/  taskqueue_enqueue (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  taskqueue_thread ; 

__attribute__((used)) static void
vtcon_ctrl_event_intr(void *xsc)
{
	struct vtcon_softc *sc;

	sc = xsc;

	/*
	 * Only some events require us to potentially block, but it
	 * easier to just defer all event handling to the taskqueue.
	 */
	taskqueue_enqueue(taskqueue_thread, &sc->vtcon_ctrl_task);
}