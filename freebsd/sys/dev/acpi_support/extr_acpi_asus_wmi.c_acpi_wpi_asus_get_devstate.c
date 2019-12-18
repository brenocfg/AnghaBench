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
struct acpi_asus_wmi_softc {int /*<<< orphan*/  dsts_id; int /*<<< orphan*/  wmi_dev; } ;
typedef  int /*<<< orphan*/  UINT32 ;

/* Variables and functions */
 int acpi_asus_wmi_evaluate_method (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
acpi_wpi_asus_get_devstate(struct acpi_asus_wmi_softc *sc,
    UINT32 dev_id, UINT32 *retval)
{

	return (acpi_asus_wmi_evaluate_method(sc->wmi_dev,
	    sc->dsts_id, dev_id, 0, retval));
}