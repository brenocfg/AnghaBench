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
struct ucom_super_softc {int sc_flag; int sc_subunits; int /*<<< orphan*/  sc_tq; int /*<<< orphan*/ * sc_sysctl_ttyports; int /*<<< orphan*/ * sc_sysctl_ttyname; } ;
struct ucom_softc {int sc_flag; } ;

/* Variables and functions */
 int UCOM_FLAG_ATTACHED ; 
 int UCOM_FLAG_WAIT_REFS ; 
 int /*<<< orphan*/  sysctl_remove_oid (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ucom_detach_tty (struct ucom_super_softc*,struct ucom_softc*) ; 
 int /*<<< orphan*/  ucom_drain (struct ucom_super_softc*) ; 
 int /*<<< orphan*/  ucom_unref (struct ucom_super_softc*) ; 
 int /*<<< orphan*/  usb_proc_drain (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_proc_free (int /*<<< orphan*/ *) ; 

void
ucom_detach(struct ucom_super_softc *ssc, struct ucom_softc *sc)
{
	int subunit;

	if (!(ssc->sc_flag & UCOM_FLAG_ATTACHED))
		return;		/* not initialized */

	if (ssc->sc_sysctl_ttyname != NULL) {
		sysctl_remove_oid(ssc->sc_sysctl_ttyname, 1, 0);
		ssc->sc_sysctl_ttyname = NULL;
	}

	if (ssc->sc_sysctl_ttyports != NULL) {
		sysctl_remove_oid(ssc->sc_sysctl_ttyports, 1, 0);
		ssc->sc_sysctl_ttyports = NULL;
	}

	usb_proc_drain(&ssc->sc_tq);

	for (subunit = 0; subunit < ssc->sc_subunits; subunit++) {
		if (sc[subunit].sc_flag & UCOM_FLAG_ATTACHED) {

			ucom_detach_tty(ssc, &sc[subunit]);

			/* avoid duplicate detach */
			sc[subunit].sc_flag &= ~UCOM_FLAG_ATTACHED;
		}
	}
	usb_proc_free(&ssc->sc_tq);

	ucom_unref(ssc);

	if (ssc->sc_flag & UCOM_FLAG_WAIT_REFS)
		ucom_drain(ssc);

	/* make sure we don't detach twice */
	ssc->sc_flag &= ~UCOM_FLAG_ATTACHED;
}