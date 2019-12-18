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
typedef  int /*<<< orphan*/ * t_Handle ;
typedef  scalar_t__ t_Error ;
struct dtsec_softc {int /*<<< orphan*/  sc_dev; int /*<<< orphan*/  sc_rx_fqid; int /*<<< orphan*/ * sc_rx_fqr; } ;

/* Variables and functions */
 int /*<<< orphan*/  DTSEC_RM_FQR_RX_CHANNEL ; 
 int /*<<< orphan*/  DTSEC_RM_FQR_RX_WQ ; 
 int EIO ; 
 scalar_t__ E_OK ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dtsec_rm_fqr_rx_callback ; 
 int /*<<< orphan*/  dtsec_rm_fqr_rx_free (struct dtsec_softc*) ; 
 int /*<<< orphan*/ * qman_fqr_create (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qman_fqr_get_base_fqid (int /*<<< orphan*/ *) ; 
 scalar_t__ qman_fqr_register_cb (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct dtsec_softc*) ; 

int
dtsec_rm_fqr_rx_init(struct dtsec_softc *sc)
{
	t_Error error;
	t_Handle fqr;

	/* Default Frame Queue */
	fqr = qman_fqr_create(1, DTSEC_RM_FQR_RX_CHANNEL, DTSEC_RM_FQR_RX_WQ,
	    false, 0, false, false, true, false, 0, 0, 0);
	if (fqr == NULL) {
		device_printf(sc->sc_dev, "could not create default RX queue"
		    "\n");
		return (EIO);
	}

	sc->sc_rx_fqr = fqr;
	sc->sc_rx_fqid = qman_fqr_get_base_fqid(fqr);

	error = qman_fqr_register_cb(fqr, dtsec_rm_fqr_rx_callback, sc);
	if (error != E_OK) {
		device_printf(sc->sc_dev, "could not register RX callback\n");
		dtsec_rm_fqr_rx_free(sc);
		return (EIO);
	}

	return (0);
}