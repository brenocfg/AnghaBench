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
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  u_int ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int CS_READ (int,int) ; 
 int /*<<< orphan*/  CS_WRITE (int,int,int) ; 
 int OFW_PCI_LATENCY ; 
 int PCIB_BCR_MASTER_ABORT_MODE ; 
 int PCIB_BCR_PERR_ENABLE ; 
 int PCIB_BCR_SERR_ENABLE ; 
 int PCIM_HDRTYPE ; 
 int PCIM_HDRTYPE_BRIDGE ; 
 int PCIR_BRIDGECTL_1 ; 
 int PCIR_CACHELNSZ ; 
 int PCIR_DEVICE ; 
 int PCIR_HDRTYPE ; 
 int PCIR_INTLINE ; 
 int PCIR_LATTIMER ; 
 int PCIR_MINGNT ; 
 int PCIR_SECLAT_1 ; 
 int PCIR_VENDOR ; 
 int PCI_INVALID_IRQ ; 
 int STRBUF_LINESZ ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int min (int,int) ; 

__attribute__((used)) static void
ofw_pcibus_setup_device(device_t bridge, uint32_t clock, u_int busno,
    u_int slot, u_int func)
{
#define	CS_READ(n, w)							\
	PCIB_READ_CONFIG(bridge, busno, slot, func, (n), (w))
#define	CS_WRITE(n, v, w)						\
	PCIB_WRITE_CONFIG(bridge, busno, slot, func, (n), (v), (w))

#ifndef SUN4V
	uint32_t reg;

	/*
	 * Initialize the latency timer register for busmaster devices to
	 * work properly.  This is another task which the firmware doesn't
	 * always perform.  The Min_Gnt register can be used to compute its
	 * recommended value: it contains the desired latency in units of
	 * 1/4 us assuming a clock rate of 33MHz.  To calculate the correct
	 * latency timer value, the clock frequency of the bus (defaulting
	 * to 33MHz) should be used and no wait states assumed.
	 * For bridges, we additionally set up the bridge control and the
	 * secondary latency registers.
	 */
	if ((CS_READ(PCIR_HDRTYPE, 1) & PCIM_HDRTYPE) ==
	    PCIM_HDRTYPE_BRIDGE) {
		reg = CS_READ(PCIR_BRIDGECTL_1, 1);
		reg |= PCIB_BCR_MASTER_ABORT_MODE | PCIB_BCR_SERR_ENABLE |
		    PCIB_BCR_PERR_ENABLE;
#ifdef OFW_PCI_DEBUG
		device_printf(bridge,
		    "bridge %d/%d/%d: control 0x%x -> 0x%x\n",
		    busno, slot, func, CS_READ(PCIR_BRIDGECTL_1, 1), reg);
#endif /* OFW_PCI_DEBUG */
		CS_WRITE(PCIR_BRIDGECTL_1, reg, 1);

		reg = OFW_PCI_LATENCY;
#ifdef OFW_PCI_DEBUG
		device_printf(bridge,
		    "bridge %d/%d/%d: latency timer %d -> %d\n",
		    busno, slot, func, CS_READ(PCIR_SECLAT_1, 1), reg);
#endif /* OFW_PCI_DEBUG */
		CS_WRITE(PCIR_SECLAT_1, reg, 1);
	} else {
		reg = CS_READ(PCIR_MINGNT, 1);
		if ((int)reg > 0) {
			switch (clock) {
			case 33000000:
				reg *= 8;
				break;
			case 66000000:
				reg *= 4;
				break;
			}
			reg = min(reg, 255);
		} else
			reg = OFW_PCI_LATENCY;
	}
#ifdef OFW_PCI_DEBUG
	device_printf(bridge, "device %d/%d/%d: latency timer %d -> %d\n",
	    busno, slot, func, CS_READ(PCIR_LATTIMER, 1), reg);
#endif /* OFW_PCI_DEBUG */
	CS_WRITE(PCIR_LATTIMER, reg, 1);

	/*
	 * Compute a value to write into the cache line size register.
	 * The role of the streaming cache is unclear in write invalidate
	 * transfers, so it is made sure that it's line size is always
	 * reached.  Generally, the cache line size is fixed at 64 bytes
	 * by Fireplane/Safari, JBus and UPA.
	 */
	CS_WRITE(PCIR_CACHELNSZ, STRBUF_LINESZ / sizeof(uint32_t), 1);
#endif

	/*
	 * Ensure that ALi M5229 report the actual content of PCIR_PROGIF
	 * and that IDE I/O is force enabled.  The former is done in order
	 * to have unique behavior across revisions as some default to
	 * hiding bits 4-6 for compliance with PCI 2.3.  The latter is done
	 * as at least revision 0xc8 requires the PCIM_CMD_PORTEN bypass
	 * to be always enabled as otherwise even enabling PCIM_CMD_PORTEN
	 * results in an instant data access trap on Fire-based machines.
	 * Thus these quirks have to be handled before pci(4) adds the maps.
	 * Note that for older revisions bit 0 of register 0x50 enables the
	 * internal IDE function instead of force enabling IDE I/O.
	 */
	if ((CS_READ(PCIR_VENDOR, 2) == 0x10b9 &&
	    CS_READ(PCIR_DEVICE, 2) == 0x5229))
		CS_WRITE(0x50, CS_READ(0x50, 1) | 0x3, 1);

	/*
	 * The preset in the intline register is usually wrong.  Reset
	 * it to 255, so that the PCI code will reroute the interrupt if
	 * needed.
	 */
	CS_WRITE(PCIR_INTLINE, PCI_INVALID_IRQ, 1);

#undef CS_READ
#undef CS_WRITE
}