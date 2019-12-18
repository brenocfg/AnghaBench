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
struct acpi_ec_softc {scalar_t__ ec_burstactive; } ;
typedef  int EC_STATUS ;
typedef  int /*<<< orphan*/  EC_EVENT ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;

/* Variables and functions */
 int /*<<< orphan*/  AE_NO_HARDWARE_RESPONSE ; 
 int /*<<< orphan*/  AE_OK ; 
 int /*<<< orphan*/  CTR1 (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  CTR2 (int /*<<< orphan*/ ,char*,char const*,int) ; 
 int EC_FLAG_BURST_MODE ; 
 int EC_GET_CSR (struct acpi_ec_softc*) ; 
 scalar_t__ EVENT_READY (int /*<<< orphan*/ ,int) ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  KTR_ACPI ; 

__attribute__((used)) static ACPI_STATUS
EcCheckStatus(struct acpi_ec_softc *sc, const char *msg, EC_EVENT event)
{
    ACPI_STATUS status;
    EC_STATUS ec_status;

    status = AE_NO_HARDWARE_RESPONSE;
    ec_status = EC_GET_CSR(sc);
    if (sc->ec_burstactive && !(ec_status & EC_FLAG_BURST_MODE)) {
	CTR1(KTR_ACPI, "ec burst disabled in waitevent (%s)", msg);
	sc->ec_burstactive = FALSE;
    }
    if (EVENT_READY(event, ec_status)) {
	CTR2(KTR_ACPI, "ec %s wait ready, status %#x", msg, ec_status);
	status = AE_OK;
    }
    return (status);
}