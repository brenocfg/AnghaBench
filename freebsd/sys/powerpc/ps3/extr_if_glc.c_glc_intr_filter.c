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
struct glc_softc {int /*<<< orphan*/ * sc_hwirq_status; int /*<<< orphan*/  sc_interrupt_status; } ;

/* Variables and functions */
 int FILTER_SCHEDULE_THREAD ; 
 int /*<<< orphan*/  atomic_set_64 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  powerpc_sync () ; 

__attribute__((used)) static int
glc_intr_filter(void *xsc)
{
	struct glc_softc *sc = xsc; 

	powerpc_sync();
	atomic_set_64(&sc->sc_interrupt_status, *sc->sc_hwirq_status);
	return (FILTER_SCHEDULE_THREAD);
}