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
struct acpi_ec_softc {int /*<<< orphan*/  ec_sci_pend; int /*<<< orphan*/  ec_gencount; } ;
typedef  int /*<<< orphan*/  UINT32 ;
typedef  int EC_STATUS ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;
typedef  int /*<<< orphan*/  ACPI_HANDLE ;

/* Variables and functions */
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_REENABLE_GPE ; 
 int /*<<< orphan*/  AcpiOsExecute (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  CTR0 (int /*<<< orphan*/ ,char*) ; 
 int EC_EVENT_SCI ; 
 int EC_GET_CSR (struct acpi_ec_softc*) ; 
 int /*<<< orphan*/  EcGpeQueryHandler ; 
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  KTR_ACPI ; 
 int /*<<< orphan*/  OSL_GPE_HANDLER ; 
 int /*<<< orphan*/  atomic_add_int (int /*<<< orphan*/ *,int) ; 
 scalar_t__ atomic_fetchadd_int (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  atomic_store_rel_int (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  wakeup (struct acpi_ec_softc*) ; 

__attribute__((used)) static UINT32
EcGpeHandler(ACPI_HANDLE GpeDevice, UINT32 GpeNumber, void *Context)
{
    struct acpi_ec_softc *sc = Context;
    ACPI_STATUS		       Status;
    EC_STATUS		       EcStatus;

    KASSERT(Context != NULL, ("EcGpeHandler called with NULL"));
    CTR0(KTR_ACPI, "ec gpe handler start");

    /*
     * Notify EcWaitEvent() that the status register is now fresh.  If we
     * didn't do this, it wouldn't be possible to distinguish an old IBE
     * from a new one, for example when doing a write transaction (writing
     * address and then data values.)
     */
    atomic_add_int(&sc->ec_gencount, 1);
    wakeup(sc);

    /*
     * If the EC_SCI bit of the status register is set, queue a query handler.
     * It will run the query and _Qxx method later, under the lock.
     */
    EcStatus = EC_GET_CSR(sc);
    if ((EcStatus & EC_EVENT_SCI) &&
	atomic_fetchadd_int(&sc->ec_sci_pend, 1) == 0) {
	CTR0(KTR_ACPI, "ec gpe queueing query handler");
	Status = AcpiOsExecute(OSL_GPE_HANDLER, EcGpeQueryHandler, Context);
	if (ACPI_FAILURE(Status)) {
	    printf("EcGpeHandler: queuing GPE query handler failed\n");
	    atomic_store_rel_int(&sc->ec_sci_pend, 0);
	}
    }
    return (ACPI_REENABLE_GPE);
}