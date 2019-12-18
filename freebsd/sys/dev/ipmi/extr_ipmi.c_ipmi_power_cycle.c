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
struct ipmi_request {scalar_t__ ir_error; scalar_t__ ir_compcode; int /*<<< orphan*/ * ir_request; } ;

/* Variables and functions */
 int /*<<< orphan*/  DELAY (int) ; 
 int /*<<< orphan*/  IPMI_ADDR (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IPMI_ALLOC_DRIVER_REQUEST (struct ipmi_request*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IPMI_CC_POWER_CYCLE ; 
 int /*<<< orphan*/  IPMI_CHASSIS_CONTROL ; 
 int /*<<< orphan*/  IPMI_CHASSIS_REQUEST ; 
 int /*<<< orphan*/  MAX_TIMEOUT ; 
 int RB_POWERCYCLE ; 
 int cycle_wait ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  ipmi_submit_driver_request (struct ipmi_softc*,struct ipmi_request*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ipmi_power_cycle(void *arg, int howto)
{
	struct ipmi_softc *sc = arg;
	struct ipmi_request *req;

	/*
	 * Ignore everything except power cycling requests
	 */
	if ((howto & RB_POWERCYCLE) == 0)
		return;

	device_printf(sc->ipmi_dev, "Power cycling using IPMI\n");

	/*
	 * Send a CHASSIS_CONTROL command to the CHASSIS device, subcommand 2
	 * as described in IPMI v2.0 spec section 28.3.
	 */
	IPMI_ALLOC_DRIVER_REQUEST(req, IPMI_ADDR(IPMI_CHASSIS_REQUEST, 0),
	    IPMI_CHASSIS_CONTROL, 1, 0);
	req->ir_request[0] = IPMI_CC_POWER_CYCLE;

	ipmi_submit_driver_request(sc, req, MAX_TIMEOUT);

	if (req->ir_error != 0 || req->ir_compcode != 0) {
		device_printf(sc->ipmi_dev, "Power cycling via IPMI failed code %#x %#x\n",
		    req->ir_error, req->ir_compcode);
		return;
	}

	/*
	 * BMCs are notoriously slow, give it cyle_wait seconds for the power
	 * down leg of the power cycle. If that fails, fallback to the next
	 * hanlder in the shutdown_final chain and/or the platform failsafe.
	 */
	DELAY(cycle_wait * 1000 * 1000);
	device_printf(sc->ipmi_dev, "Power cycling via IPMI timed out\n");
}