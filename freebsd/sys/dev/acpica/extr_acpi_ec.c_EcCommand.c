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
typedef  int EC_STATUS ;
typedef  int /*<<< orphan*/  EC_EVENT ;
typedef  int EC_COMMAND ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;

/* Variables and functions */
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_SERIAL_ASSERT (int /*<<< orphan*/ ) ; 
 scalar_t__ ACPI_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AE_BAD_PARAMETER ; 
 int /*<<< orphan*/  AE_ERROR ; 
 int /*<<< orphan*/  CTR1 (int /*<<< orphan*/ ,char*,int) ; 
#define  EC_COMMAND_BURST_DISABLE 132 
#define  EC_COMMAND_BURST_ENABLE 131 
#define  EC_COMMAND_QUERY 130 
#define  EC_COMMAND_READ 129 
#define  EC_COMMAND_WRITE 128 
 int /*<<< orphan*/  EC_EVENT_INPUT_BUFFER_EMPTY ; 
 int /*<<< orphan*/  EC_EVENT_OUTPUT_BUFFER_FULL ; 
 int EC_FLAG_BURST_MODE ; 
 int EC_GET_CSR (struct acpi_ec_softc*) ; 
 int /*<<< orphan*/  EC_SET_CSR (struct acpi_ec_softc*,int) ; 
 int /*<<< orphan*/  EcWaitEvent (struct acpi_ec_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KTR_ACPI ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  ec ; 
 int /*<<< orphan*/  ec_burst_mode ; 

__attribute__((used)) static ACPI_STATUS
EcCommand(struct acpi_ec_softc *sc, EC_COMMAND cmd)
{
    ACPI_STATUS	status;
    EC_EVENT	event;
    EC_STATUS	ec_status;
    u_int	gen_count;

    ACPI_SERIAL_ASSERT(ec);

    /* Don't use burst mode if user disabled it. */
    if (!ec_burst_mode && cmd == EC_COMMAND_BURST_ENABLE)
	return (AE_ERROR);

    /* Decide what to wait for based on command type. */
    switch (cmd) {
    case EC_COMMAND_READ:
    case EC_COMMAND_WRITE:
    case EC_COMMAND_BURST_DISABLE:
	event = EC_EVENT_INPUT_BUFFER_EMPTY;
	break;
    case EC_COMMAND_QUERY:
    case EC_COMMAND_BURST_ENABLE:
	event = EC_EVENT_OUTPUT_BUFFER_FULL;
	break;
    default:
	device_printf(sc->ec_dev, "EcCommand: invalid command %#x\n", cmd);
	return (AE_BAD_PARAMETER);
    }

    /*
     * Ensure empty input buffer before issuing command.
     * Use generation count of zero to force a quick check.
     */
    status = EcWaitEvent(sc, EC_EVENT_INPUT_BUFFER_EMPTY, 0);
    if (ACPI_FAILURE(status))
	return (status);

    /* Run the command and wait for the chosen event. */
    CTR1(KTR_ACPI, "ec running command %#x", cmd);
    gen_count = sc->ec_gencount;
    EC_SET_CSR(sc, cmd);
    status = EcWaitEvent(sc, event, gen_count);
    if (ACPI_SUCCESS(status)) {
	/* If we succeeded, burst flag should now be present. */
	if (cmd == EC_COMMAND_BURST_ENABLE) {
	    ec_status = EC_GET_CSR(sc);
	    if ((ec_status & EC_FLAG_BURST_MODE) == 0)
		status = AE_ERROR;
	}
    } else
	device_printf(sc->ec_dev, "EcCommand: no response to %#x\n", cmd);
    return (status);
}