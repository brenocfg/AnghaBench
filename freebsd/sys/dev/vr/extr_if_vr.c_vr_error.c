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
typedef  int uint16_t ;
struct TYPE_2__ {int /*<<< orphan*/  bus_errors; } ;
struct vr_softc {scalar_t__ vr_revid; int /*<<< orphan*/  vr_dev; int /*<<< orphan*/  vr_flags; TYPE_1__ vr_stat; } ;

/* Variables and functions */
 int /*<<< orphan*/  CSR_WRITE_2 (struct vr_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int EAGAIN ; 
 int /*<<< orphan*/  PCIR_STATUS ; 
 scalar_t__ REV_ID_VT6105M_A0 ; 
 int /*<<< orphan*/  VR_F_RESTART ; 
 int /*<<< orphan*/  VR_IMR ; 
 int VR_ISR_BUSERR ; 
 int VR_ISR_LINKSTAT2 ; 
 int VR_ISR_STATSOFLOW ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int) ; 
 int pci_read_config (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pci_write_config (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int
vr_error(struct vr_softc *sc, uint16_t status)
{
	uint16_t pcis;

	status &= VR_ISR_BUSERR | VR_ISR_LINKSTAT2 | VR_ISR_STATSOFLOW;
	if ((status & VR_ISR_BUSERR) != 0) {
		status &= ~VR_ISR_BUSERR;
		sc->vr_stat.bus_errors++;
		/* Disable further interrupts. */
		CSR_WRITE_2(sc, VR_IMR, 0);
		pcis = pci_read_config(sc->vr_dev, PCIR_STATUS, 2);
		device_printf(sc->vr_dev, "PCI bus error(0x%04x) -- "
		    "resetting\n", pcis);
		pci_write_config(sc->vr_dev, PCIR_STATUS, pcis, 2);
		sc->vr_flags |= VR_F_RESTART;
		return (EAGAIN);
	}
	if ((status & VR_ISR_LINKSTAT2) != 0) {
		/* Link state change, duplex changes etc. */
		status &= ~VR_ISR_LINKSTAT2;
	}
	if ((status & VR_ISR_STATSOFLOW) != 0) {
		status &= ~VR_ISR_STATSOFLOW;
		if (sc->vr_revid >= REV_ID_VT6105M_A0) {
			/* Update MIB counters. */
		}
	}

	if (status != 0)
		device_printf(sc->vr_dev,
		    "unhandled interrupt, status = 0x%04x\n", status);
	return (0);
}