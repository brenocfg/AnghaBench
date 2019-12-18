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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/ * t_Handle ;
struct qman_softc {int /*<<< orphan*/  sc_dev; } ;
typedef  int /*<<< orphan*/  e_QmFqrCounters ;

/* Variables and functions */
 int /*<<< orphan*/  QM_FQR_GetCounter (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * qman_portal_setup (struct qman_softc*) ; 
 struct qman_softc* qman_sc ; 
 int /*<<< orphan*/  sched_pin () ; 
 int /*<<< orphan*/  sched_unpin () ; 

uint32_t
qman_fqr_get_counter(t_Handle fqr, uint32_t fqid_off,
    e_QmFqrCounters counter)
{
	struct qman_softc *sc;
	uint32_t val;
	t_Handle portal;

	sc = qman_sc;
	sched_pin();

	/* Ensure we have got QMan port initialized */
	portal = qman_portal_setup(sc);
	if (portal == NULL) {
		device_printf(sc->sc_dev, "could not setup QMan portal\n");
		sched_unpin();
		return (0);
	}

	val = QM_FQR_GetCounter(fqr, portal, fqid_off, counter);

	sched_unpin();

	return (val);
}