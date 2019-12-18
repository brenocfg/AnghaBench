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
struct ipmi_softc {int ipmi_driver_requests_polled; int /*<<< orphan*/  ipmi_dev; int /*<<< orphan*/  ipmi_driver_request; int /*<<< orphan*/  ipmi_enqueue_request; int /*<<< orphan*/  ipmi_startup; } ;

/* Variables and functions */
 int ENXIO ; 
 int INB (struct ipmi_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KCS_CTL_STS ; 
 int KCS_STATUS_OBF ; 
 scalar_t__ KCS_STATUS_STATE (int) ; 
 scalar_t__ KCS_STATUS_STATE_IDLE ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  ipmi_polled_enqueue_request ; 
 int /*<<< orphan*/  kcs_driver_request ; 
 int /*<<< orphan*/  kcs_error (struct ipmi_softc*) ; 
 int /*<<< orphan*/  kcs_startup ; 

int
ipmi_kcs_attach(struct ipmi_softc *sc)
{
	int status;

	/* Setup function pointers. */
	sc->ipmi_startup = kcs_startup;
	sc->ipmi_enqueue_request = ipmi_polled_enqueue_request;
	sc->ipmi_driver_request = kcs_driver_request;
	sc->ipmi_driver_requests_polled = 1;

	/* See if we can talk to the controller. */
	status = INB(sc, KCS_CTL_STS);
	if (status == 0xff) {
		device_printf(sc->ipmi_dev, "couldn't find it\n");
		return (ENXIO);
	}

#ifdef KCS_DEBUG
	device_printf(sc->ipmi_dev, "KCS: initial state: %02x\n", status);
#endif
	if (status & KCS_STATUS_OBF ||
	    KCS_STATUS_STATE(status) != KCS_STATUS_STATE_IDLE)
		kcs_error(sc);

	return (0);
}