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
struct hpet_softc {int /*<<< orphan*/  acpi_uid; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 struct hpet_softc* device_get_softc (int /*<<< orphan*/ ) ; 

uint32_t
hpet_get_uid(device_t dev)
{
	struct hpet_softc *sc;

	sc = device_get_softc(dev);
	return (sc->acpi_uid);
}