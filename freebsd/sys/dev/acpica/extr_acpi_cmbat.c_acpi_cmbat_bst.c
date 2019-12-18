#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  volt; int /*<<< orphan*/  cap; int /*<<< orphan*/  rate; int /*<<< orphan*/  state; } ;
struct acpi_cmbat_softc {TYPE_1__ bst; } ;
struct acpi_bst {int /*<<< orphan*/  state; int /*<<< orphan*/  volt; int /*<<< orphan*/  cap; int /*<<< orphan*/  rate; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_BATT_STAT_NOT_PRESENT ; 
 int /*<<< orphan*/  ACPI_SERIAL_BEGIN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_SERIAL_END (int /*<<< orphan*/ ) ; 
 scalar_t__ acpi_BatteryIsPresent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_cmbat_get_bst (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmbat ; 
 struct acpi_cmbat_softc* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
acpi_cmbat_bst(device_t dev, struct acpi_bst *bstp)
{
    struct acpi_cmbat_softc *sc;

    sc = device_get_softc(dev);

    ACPI_SERIAL_BEGIN(cmbat);
    if (acpi_BatteryIsPresent(dev)) {
	acpi_cmbat_get_bst(dev);
	bstp->state = sc->bst.state;
	bstp->rate = sc->bst.rate;
	bstp->cap = sc->bst.cap;
	bstp->volt = sc->bst.volt;
    } else
	bstp->state = ACPI_BATT_STAT_NOT_PRESENT;
    ACPI_SERIAL_END(cmbat);

    return (0);
}