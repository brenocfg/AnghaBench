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
struct rt_softc {int /*<<< orphan*/  periodic_task; int /*<<< orphan*/  taskqueue; } ;

/* Variables and functions */
 int /*<<< orphan*/  RT_DEBUG_PERIODIC ; 
 int /*<<< orphan*/  RT_DPRINTF (struct rt_softc*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  taskqueue_enqueue (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
rt_periodic(void *arg)
{
	struct rt_softc *sc;

	sc = arg;
	RT_DPRINTF(sc, RT_DEBUG_PERIODIC, "periodic\n");
	taskqueue_enqueue(sc->taskqueue, &sc->periodic_task);
}