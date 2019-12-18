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
struct ichwd_softc {int tco_version; int /*<<< orphan*/  device; int /*<<< orphan*/  ich; } ;

/* Variables and functions */
 int EIO ; 
 int ICH_GCS_NO_REBOOT ; 
 int /*<<< orphan*/  ICH_GEN_STA ; 
 int ICH_GEN_STA_NO_REBOOT ; 
 int ICH_PMC_NO_REBOOT ; 
 int SMB_GC_NO_REBOOT ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int ichwd_read_gc_4 (struct ichwd_softc*,int /*<<< orphan*/ ) ; 
 int ichwd_read_gcs_4 (struct ichwd_softc*,int /*<<< orphan*/ ) ; 
 int ichwd_read_pmc_4 (struct ichwd_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ichwd_verbose_printf (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  ichwd_write_gc_4 (struct ichwd_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ichwd_write_gcs_4 (struct ichwd_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ichwd_write_pmc_4 (struct ichwd_softc*,int /*<<< orphan*/ ,int) ; 
 int pci_read_config (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pci_write_config (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static __inline int
ichwd_clear_noreboot(struct ichwd_softc *sc)
{
	uint32_t status;
	int rc = 0;

	/* try to clear the NO_REBOOT bit */
	switch (sc->tco_version) {
	case 1:
		status = pci_read_config(sc->ich, ICH_GEN_STA, 1);
		status &= ~ICH_GEN_STA_NO_REBOOT;
		pci_write_config(sc->ich, ICH_GEN_STA, status, 1);
		status = pci_read_config(sc->ich, ICH_GEN_STA, 1);
		if (status & ICH_GEN_STA_NO_REBOOT)
			rc = EIO;
		break;
	case 2:
		status = ichwd_read_gcs_4(sc, 0);
		status &= ~ICH_GCS_NO_REBOOT;
		ichwd_write_gcs_4(sc, 0, status);
		status = ichwd_read_gcs_4(sc, 0);
		if (status & ICH_GCS_NO_REBOOT)
			rc = EIO;
		break;
	case 3:
		status = ichwd_read_pmc_4(sc, 0);
		status &= ~ICH_PMC_NO_REBOOT;
		ichwd_write_pmc_4(sc, 0, status);
		status = ichwd_read_pmc_4(sc, 0);
		if (status & ICH_PMC_NO_REBOOT)
			rc = EIO;
		break;
	case 4:
		status = ichwd_read_gc_4(sc, 0);
		status &= ~SMB_GC_NO_REBOOT;
		ichwd_write_gc_4(sc, 0, status);
		status = ichwd_read_gc_4(sc, 0);
		if (status & SMB_GC_NO_REBOOT)
			rc = EIO;
		break;
	default:
		ichwd_verbose_printf(sc->device,
		    "Unknown TCO Version: %d, can't set NO_REBOOT.\n",
		    sc->tco_version);
		break;
	}

	if (rc)
		device_printf(sc->device,
		    "ICH WDT present but disabled in BIOS or hardware\n");

	return (rc);
}