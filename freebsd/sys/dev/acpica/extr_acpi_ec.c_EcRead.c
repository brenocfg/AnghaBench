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
 scalar_t__ ACPI_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AE_OK ; 
 int /*<<< orphan*/  CTR1 (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EC_COMMAND_READ ; 
 int /*<<< orphan*/  EC_EVENT_INPUT_BUFFER_EMPTY ; 
 int /*<<< orphan*/  EC_EVENT_OUTPUT_BUFFER_FULL ; 
 int /*<<< orphan*/  EC_GET_DATA (struct acpi_ec_softc*) ; 
 int /*<<< orphan*/  EC_SET_DATA (struct acpi_ec_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EcCheckStatus (struct acpi_ec_softc*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EcCommand (struct acpi_ec_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EcWaitEvent (struct acpi_ec_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KTR_ACPI ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ec ; 

__attribute__((used)) static ACPI_STATUS
EcRead(struct acpi_ec_softc *sc, UINT8 Address, UINT8 *Data)
{
    ACPI_STATUS	status;
    u_int gen_count;
    int retry;

    ACPI_SERIAL_ASSERT(ec);
    CTR1(KTR_ACPI, "ec read from %#x", Address);

    for (retry = 0; retry < 2; retry++) {
	status = EcCommand(sc, EC_COMMAND_READ);
	if (ACPI_FAILURE(status))
	    return (status);

	gen_count = sc->ec_gencount;
	EC_SET_DATA(sc, Address);
	status = EcWaitEvent(sc, EC_EVENT_OUTPUT_BUFFER_FULL, gen_count);
	if (ACPI_SUCCESS(status)) {
	    *Data = EC_GET_DATA(sc);
	    return (AE_OK);
	}
	if (ACPI_FAILURE(EcCheckStatus(sc, "retr_check",
	    EC_EVENT_INPUT_BUFFER_EMPTY)))
	    break;
    }
    device_printf(sc->ec_dev, "EcRead: failed waiting to get data\n");
    return (status);
}