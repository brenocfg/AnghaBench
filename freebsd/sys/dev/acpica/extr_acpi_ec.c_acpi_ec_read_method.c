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
typedef  int /*<<< orphan*/  u_int ;
struct acpi_ec_softc {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;
typedef  int /*<<< orphan*/  UINT64 ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;

/* Variables and functions */
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_READ ; 
 int ENXIO ; 
 int /*<<< orphan*/  EcSpaceHandler (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,struct acpi_ec_softc*,int /*<<< orphan*/ *) ; 
 struct acpi_ec_softc* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
acpi_ec_read_method(device_t dev, u_int addr, UINT64 *val, int width)
{
    struct acpi_ec_softc *sc;
    ACPI_STATUS status;

    sc = device_get_softc(dev);
    status = EcSpaceHandler(ACPI_READ, addr, width * 8, val, sc, NULL);
    if (ACPI_FAILURE(status))
	return (ENXIO);
    return (0);
}