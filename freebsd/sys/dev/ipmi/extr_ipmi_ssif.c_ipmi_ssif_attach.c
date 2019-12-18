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
struct ipmi_softc {int ipmi_ssif_smbus_address; int /*<<< orphan*/  ipmi_driver_request; int /*<<< orphan*/  ipmi_enqueue_request; int /*<<< orphan*/  ipmi_startup; int /*<<< orphan*/  ipmi_ssif_smbus; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  ipmi_polled_enqueue_request ; 
 int /*<<< orphan*/  ssif_driver_request ; 
 int /*<<< orphan*/  ssif_startup ; 

int
ipmi_ssif_attach(struct ipmi_softc *sc, device_t smbus, int smbus_address)
{

	/* Setup smbus address. */
	sc->ipmi_ssif_smbus = smbus;
	sc->ipmi_ssif_smbus_address = smbus_address;

	/* Setup function pointers. */
	sc->ipmi_startup = ssif_startup;
	sc->ipmi_enqueue_request = ipmi_polled_enqueue_request;
	sc->ipmi_driver_request = ssif_driver_request;

	return (0);
}