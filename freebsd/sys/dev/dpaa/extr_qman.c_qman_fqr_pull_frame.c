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
typedef  int /*<<< orphan*/  t_Error ;
typedef  int /*<<< orphan*/  t_DpaaFD ;
struct qman_softc {int /*<<< orphan*/  sc_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  E_NOT_SUPPORTED ; 
 int /*<<< orphan*/  QM_FQR_PullFrame (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * qman_portal_setup (struct qman_softc*) ; 
 struct qman_softc* qman_sc ; 
 int /*<<< orphan*/  sched_pin () ; 
 int /*<<< orphan*/  sched_unpin () ; 

t_Error
qman_fqr_pull_frame(t_Handle fqr, uint32_t fqid_off, t_DpaaFD *frame)
{
	struct qman_softc *sc;
	t_Error error;
	t_Handle portal;

	sc = qman_sc;
	sched_pin();

	/* Ensure we have got QMan port initialized */
	portal = qman_portal_setup(sc);
	if (portal == NULL) {
		device_printf(sc->sc_dev, "could not setup QMan portal\n");
		sched_unpin();
		return (E_NOT_SUPPORTED);
	}

	error = QM_FQR_PullFrame(fqr, portal, fqid_off, frame);

	sched_unpin();

	return (error);
}