#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u_char ;
typedef  int /*<<< orphan*/  bus_datum ;
struct TYPE_5__ {int /*<<< orphan*/  bus_type; } ;
struct TYPE_4__ {int mpfb2; } ;

/* Variables and functions */
 int IOAPIC_MAX_ID ; 
 int MPFB2_IMCR_PRESENT ; 
 int /*<<< orphan*/  M_MPTABLE ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int /*<<< orphan*/  NOBUS ; 
 TYPE_2__* busses ; 
 int inb (int) ; 
 int /*<<< orphan*/  ioapic_register (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ ** ioapics ; 
 TYPE_2__* malloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* mpfps ; 
 int /*<<< orphan*/  mptable_count_items () ; 
 int mptable_maxbusid ; 
 int /*<<< orphan*/  mptable_parse_apics_and_busses () ; 
 int /*<<< orphan*/  mptable_parse_ints () ; 
 int /*<<< orphan*/  mptable_pci_setup () ; 
 int /*<<< orphan*/  outb (int,int) ; 

__attribute__((used)) static int
mptable_setup_io(void)
{
	int i;
	u_char byte;

	/* First, we count individual items and allocate arrays. */
	mptable_count_items();
	busses = malloc((mptable_maxbusid + 1) * sizeof(bus_datum), M_MPTABLE,
	    M_WAITOK);
	for (i = 0; i <= mptable_maxbusid; i++)
		busses[i].bus_type = NOBUS;

	/* Second, we run through adding I/O APIC's and buses. */
	mptable_parse_apics_and_busses();	

	/* Third, we run through the table tweaking interrupt sources. */
	mptable_parse_ints();

	/* Fourth, we register all the I/O APIC's. */
	for (i = 0; i <= IOAPIC_MAX_ID; i++)
		if (ioapics[i] != NULL)
			ioapic_register(ioapics[i]);

	/* Fifth, we setup data structures to handle PCI interrupt routing. */
	mptable_pci_setup();

	/* Finally, we throw the switch to enable the I/O APIC's. */
	if (mpfps->mpfb2 & MPFB2_IMCR_PRESENT) {
		outb(0x22, 0x70);	/* select IMCR */
		byte = inb(0x23);	/* current contents */
		byte |= 0x01;		/* mask external INTR */
		outb(0x23, byte);	/* disconnect 8259s/NMI */
	}

	return (0);
}