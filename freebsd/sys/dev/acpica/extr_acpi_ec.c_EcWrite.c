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
struct acpi_ec_softc {int /*<<< orphan*/  ec_dev; int /*<<< orphan*/  ec_gencount; } ;
typedef  int /*<<< orphan*/  UINT8 ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;

/* Variables and functions */
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_SERIAL_ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AE_OK ; 
 int /*<<< orphan*/  CTR2 (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EC_COMMAND_WRITE ; 
 int /*<<< orphan*/  EC_EVENT_INPUT_BUFFER_EMPTY ; 
 int /*<<< orphan*/  EC_SET_DATA (struct acpi_ec_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EcCommand (struct acpi_ec_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EcWaitEvent (struct acpi_ec_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KTR_ACPI ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ec ; 

__attribute__((used)) static ACPI_STATUS
EcWrite(struct acpi_ec_softc *sc, UINT8 Address, UINT8 Data)
{
    ACPI_STATUS	status;
    u_int gen_count;

    ACPI_SERIAL_ASSERT(ec);
    CTR2(KTR_ACPI, "ec write to %#x, data %#x", Address, Data);

    status = EcCommand(sc, EC_COMMAND_WRITE);
    if (ACPI_FAILURE(status))
	return (status);

    gen_count = sc->ec_gencount;
    EC_SET_DATA(sc, Address);
    status = EcWaitEvent(sc, EC_EVENT_INPUT_BUFFER_EMPTY, gen_count);
    if (ACPI_FAILURE(status)) {
	device_printf(sc->ec_dev, "EcWrite: failed waiting for sent address\n");
	return (status);
    }

    gen_count = sc->ec_gencount;
    EC_SET_DATA(sc, Data);
    status = EcWaitEvent(sc, EC_EVENT_INPUT_BUFFER_EMPTY, gen_count);
    if (ACPI_FAILURE(status)) {
	device_printf(sc->ec_dev, "EcWrite: failed waiting for sent data\n");
	return (status);
    }

    return (AE_OK);
}