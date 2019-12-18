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
struct ipmi_softc {int /*<<< orphan*/  ipmi_dev; } ;
struct ipmi_request {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IPMI_ADDR (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IPMI_ALLOC_DRIVER_REQUEST (struct ipmi_request*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IPMI_APP_REQUEST ; 
 int /*<<< orphan*/  IPMI_RESET_WDOG ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int ipmi_submit_driver_request (struct ipmi_softc*,struct ipmi_request*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ipmi_reset_watchdog(struct ipmi_softc *sc)
{
	struct ipmi_request *req;
	int error;

	IPMI_ALLOC_DRIVER_REQUEST(req, IPMI_ADDR(IPMI_APP_REQUEST, 0),
	    IPMI_RESET_WDOG, 0, 0);
	error = ipmi_submit_driver_request(sc, req, 0);
	if (error)
		device_printf(sc->ipmi_dev, "Failed to reset watchdog\n");
	return (error);
}