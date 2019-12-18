#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_5__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_int ;
struct TYPE_7__ {int SciInterrupt; } ;
struct TYPE_6__ {int /*<<< orphan*/ * io_apic; } ;

/* Variables and functions */
 scalar_t__ ACPI_FAILURE (int) ; 
 int /*<<< orphan*/  ACPI_INTR_APIC ; 
 char* AcpiFormatException (int) ; 
 TYPE_5__ AcpiGbl_FADT ; 
 int /*<<< orphan*/  INTR_POLARITY_LOW ; 
 int /*<<< orphan*/  INTR_TRIGGER_LEVEL ; 
 int IOAPIC_MAX_ID ; 
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  M_MADT ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int /*<<< orphan*/  acpi_SetDefaultIntrModel (int /*<<< orphan*/ ) ; 
 int acpi_Startup () ; 
 int /*<<< orphan*/  free (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ioapic_register (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ioapic_set_polarity (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ioapic_set_triggermode (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* ioapics ; 
 TYPE_1__* lapics ; 
 scalar_t__ madt_find_interrupt (int,void**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  madt_found_sci_override ; 
 int /*<<< orphan*/  madt_parse_apics ; 
 int /*<<< orphan*/  madt_parse_ints ; 
 int /*<<< orphan*/  madt_walk_table (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_1__* malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static int
madt_setup_io(void)
{
	void *ioapic;
	u_int pin;
	int i;

	KASSERT(lapics != NULL, ("local APICs not initialized"));

	/* Try to initialize ACPI so that we can access the FADT. */
	i = acpi_Startup();
	if (ACPI_FAILURE(i)) {
		printf("MADT: ACPI Startup failed with %s\n",
		    AcpiFormatException(i));
		printf("Try disabling either ACPI or apic support.\n");
		panic("Using MADT but ACPI doesn't work");
	}

	ioapics = malloc(sizeof(*ioapics) * (IOAPIC_MAX_ID + 1), M_MADT,
	    M_WAITOK | M_ZERO);

	/* First, we run through adding I/O APIC's. */
	madt_walk_table(madt_parse_apics, NULL);

	/* Second, we run through the table tweaking interrupt sources. */
	madt_walk_table(madt_parse_ints, NULL);

	/*
	 * If there was not an explicit override entry for the SCI,
	 * force it to use level trigger and active-low polarity.
	 */
	if (!madt_found_sci_override) {
		if (madt_find_interrupt(AcpiGbl_FADT.SciInterrupt, &ioapic,
		    &pin) != 0)
			printf("MADT: Could not find APIC for SCI IRQ %u\n",
			    AcpiGbl_FADT.SciInterrupt);
		else {
			printf(
	"MADT: Forcing active-low polarity and level trigger for SCI\n");
			ioapic_set_polarity(ioapic, pin, INTR_POLARITY_LOW);
			ioapic_set_triggermode(ioapic, pin, INTR_TRIGGER_LEVEL);
		}
	}

	/* Third, we register all the I/O APIC's. */
	for (i = 0; i <= IOAPIC_MAX_ID; i++)
		if (ioapics[i].io_apic != NULL)
			ioapic_register(ioapics[i].io_apic);

	/* Finally, we throw the switch to enable the I/O APIC's. */
	acpi_SetDefaultIntrModel(ACPI_INTR_APIC);

	free(ioapics, M_MADT);
	ioapics = NULL;

	/* NB: this is the last use of the lapics array. */
	free(lapics, M_MADT);
	lapics = NULL;

	return (0);
}