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
struct aibs_softc {int sc_ggrp_method; int /*<<< orphan*/ * sc_fan_sysctl; int /*<<< orphan*/ * sc_temp_sysctl; int /*<<< orphan*/ * sc_volt_sysctl; int /*<<< orphan*/  sc_ah; int /*<<< orphan*/  sc_dev; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  AIBS_SENS_TYPE_FAN ; 
 int /*<<< orphan*/  AIBS_SENS_TYPE_TEMP ; 
 int /*<<< orphan*/  AIBS_SENS_TYPE_VOLT ; 
 int /*<<< orphan*/  acpi_get_handle (int /*<<< orphan*/ ) ; 
 int aibs_attach_ggrp (struct aibs_softc*) ; 
 int aibs_attach_sif (struct aibs_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  aibs_detach (int /*<<< orphan*/ ) ; 
 struct aibs_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sysctl_remove_oid (int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static int
aibs_attach(device_t dev)
{
	struct aibs_softc *sc = device_get_softc(dev);
	int err;

	sc->sc_dev = dev;
	sc->sc_ah = acpi_get_handle(dev);

	sc->sc_ggrp_method = false;
	err = aibs_attach_sif(sc, AIBS_SENS_TYPE_VOLT);
	if (err == 0)
		err = aibs_attach_sif(sc, AIBS_SENS_TYPE_TEMP);
	if (err == 0)
		err = aibs_attach_sif(sc, AIBS_SENS_TYPE_FAN);

	if (err == 0)
		return (0);

	/* Clean up whatever was allocated earlier. */
	if (sc->sc_volt_sysctl != NULL)
		sysctl_remove_oid(sc->sc_volt_sysctl, true, true);
	if (sc->sc_temp_sysctl != NULL)
		sysctl_remove_oid(sc->sc_temp_sysctl, true, true);
	if (sc->sc_fan_sysctl != NULL)
		sysctl_remove_oid(sc->sc_fan_sysctl, true, true);
	aibs_detach(dev);

	sc->sc_ggrp_method = true;
	err = aibs_attach_ggrp(sc);
	return (err);
}