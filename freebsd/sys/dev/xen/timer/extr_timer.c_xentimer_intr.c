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
struct TYPE_2__ {int /*<<< orphan*/  et_arg; int /*<<< orphan*/  (* et_event_cb ) (TYPE_1__*,int /*<<< orphan*/ ) ;scalar_t__ et_active; } ;
struct xentimer_softc {TYPE_1__ et; } ;
struct xentimer_pcpu_data {scalar_t__ timer; int /*<<< orphan*/  last_processed; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPCPU_GET (int /*<<< orphan*/ ) ; 
 struct xentimer_pcpu_data* DPCPU_PTR (int /*<<< orphan*/ ) ; 
 int FILTER_HANDLED ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vcpu_info ; 
 int /*<<< orphan*/  xen_fetch_vcpu_time (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xentimer_pcpu ; 

__attribute__((used)) static int
xentimer_intr(void *arg)
{
	struct xentimer_softc *sc = (struct xentimer_softc *)arg;
	struct xentimer_pcpu_data *pcpu = DPCPU_PTR(xentimer_pcpu);

	pcpu->last_processed = xen_fetch_vcpu_time(DPCPU_GET(vcpu_info));
	if (pcpu->timer != 0 && sc->et.et_active)
		sc->et.et_event_cb(&sc->et, sc->et.et_arg);

	return (FILTER_HANDLED);
}