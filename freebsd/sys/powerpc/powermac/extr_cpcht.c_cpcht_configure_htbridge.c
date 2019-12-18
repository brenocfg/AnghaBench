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
typedef  int uint32_t ;
typedef  int u_int ;
struct ofw_pci_register {int /*<<< orphan*/  phys_hi; } ;
struct cpcht_softc {int sc_populated_slots; int sc_data; TYPE_1__* htirq_map; } ;
typedef  int /*<<< orphan*/  phandle_t ;
typedef  int /*<<< orphan*/  pcir ;
typedef  int /*<<< orphan*/  pcell_t ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_2__ {int ht_source; int ht_base; int eoi_data; int apple_eoi; int /*<<< orphan*/  irq_type; } ;

/* Variables and functions */
 int HTAPIC_MASK ; 
 int /*<<< orphan*/  IRQ_HT ; 
 int OFW_PCI_PHYS_HI_BUS (int /*<<< orphan*/ ) ; 
 int OFW_PCI_PHYS_HI_DEVICE (int /*<<< orphan*/ ) ; 
 int OFW_PCI_PHYS_HI_FUNCTION (int /*<<< orphan*/ ) ; 
 int OF_getencprop (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int) ; 
 int PCIB_READ_CONFIG (int /*<<< orphan*/ ,int,int,int,int,int) ; 
 int /*<<< orphan*/  PCIB_WRITE_CONFIG (int /*<<< orphan*/ ,int,int,int,int,int,int) ; 
 int PCICAP_ID ; 
 int PCICAP_NEXTPTR ; 
 int PCIM_HTCAP_INTERRUPT ; 
 int PCIM_HTCMD_CAP_MASK ; 
 int PCIM_STATUS_CAPPRESENT ; 
 int PCIR_CAP_PTR ; 
 int PCIR_DEVVENDOR ; 
 int PCIR_HT_COMMAND ; 
 int PCIR_STATUS ; 
 int PCIY_HT ; 
 struct cpcht_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int,int,int) ; 

__attribute__((used)) static void
cpcht_configure_htbridge(device_t dev, phandle_t child)
{
	struct cpcht_softc *sc;
	struct ofw_pci_register pcir;
	int ptr, nextptr;
	uint32_t vend, val;
	int i, nirq, irq;
	u_int b, f, s;

	sc = device_get_softc(dev);
	if (OF_getencprop(child, "reg", (pcell_t *)&pcir, sizeof(pcir)) == -1)
		return;

	b = OFW_PCI_PHYS_HI_BUS(pcir.phys_hi);
	s = OFW_PCI_PHYS_HI_DEVICE(pcir.phys_hi);
	f = OFW_PCI_PHYS_HI_FUNCTION(pcir.phys_hi);

	/*
	 * Mark this slot is populated. The remote south bridge does
	 * not like us talking to unpopulated slots on the root bus.
	 */
	sc->sc_populated_slots |= (1 << s);

	/*
	 * Next build up any HT->MPIC mappings for this sub-bus. One would
	 * naively hope that enabling, disabling, and EOIing interrupts would
	 * cause the appropriate HT bus transactions to that effect. This is
	 * not the case.
	 *
	 * Instead, we have to muck about on the HT peer's root PCI bridges,
	 * figure out what interrupts they send, enable them, and cache
	 * the location of their WaitForEOI registers so that we can
	 * send EOIs later.
	 */

	/* All the devices we are interested in have caps */
	if (!(PCIB_READ_CONFIG(dev, b, s, f, PCIR_STATUS, 2)
	    & PCIM_STATUS_CAPPRESENT))
		return;

	nextptr = PCIB_READ_CONFIG(dev, b, s, f, PCIR_CAP_PTR, 1);
	while (nextptr != 0) {
		ptr = nextptr;
		nextptr = PCIB_READ_CONFIG(dev, b, s, f,
		    ptr + PCICAP_NEXTPTR, 1);

		/* Find the HT IRQ capabilities */
		if (PCIB_READ_CONFIG(dev, b, s, f,
		    ptr + PCICAP_ID, 1) != PCIY_HT)
			continue;

		val = PCIB_READ_CONFIG(dev, b, s, f, ptr + PCIR_HT_COMMAND, 2);
		if ((val & PCIM_HTCMD_CAP_MASK) != PCIM_HTCAP_INTERRUPT)
			continue;

		/* Ask for the IRQ count */
		PCIB_WRITE_CONFIG(dev, b, s, f, ptr + PCIR_HT_COMMAND, 0x1, 1);
		nirq = PCIB_READ_CONFIG(dev, b, s, f, ptr + 4, 4);
		nirq = ((nirq >> 16) & 0xff) + 1;

		device_printf(dev, "%d HT IRQs on device %d.%d\n", nirq, s, f);

		for (i = 0; i < nirq; i++) {
			PCIB_WRITE_CONFIG(dev, b, s, f,
			     ptr + PCIR_HT_COMMAND, 0x10 + (i << 1), 1);
			irq = PCIB_READ_CONFIG(dev, b, s, f, ptr + 4, 4);

			/*
			 * Mask this interrupt for now.
			 */
			PCIB_WRITE_CONFIG(dev, b, s, f, ptr + 4,
			    irq | HTAPIC_MASK, 4);
			irq = (irq >> 16) & 0xff;

			sc->htirq_map[irq].irq_type = IRQ_HT;
			sc->htirq_map[irq].ht_source = i;
			sc->htirq_map[irq].ht_base = sc->sc_data + 
			    (((((s & 0x1f) << 3) | (f & 0x07)) << 8) | (ptr));

			PCIB_WRITE_CONFIG(dev, b, s, f,
			     ptr + PCIR_HT_COMMAND, 0x11 + (i << 1), 1);
			sc->htirq_map[irq].eoi_data =
			    PCIB_READ_CONFIG(dev, b, s, f, ptr + 4, 4) |
			    0x80000000;

			/*
			 * Apple uses a non-compliant IO/APIC that differs
			 * in how we signal EOIs. Check if this device was 
			 * made by Apple, and act accordingly.
			 */
			vend = PCIB_READ_CONFIG(dev, b, s, f,
			    PCIR_DEVVENDOR, 4);
			if ((vend & 0xffff) == 0x106b)
				sc->htirq_map[irq].apple_eoi = 
				 (sc->htirq_map[irq].ht_base - ptr) + 0x60;
		}
	}
}