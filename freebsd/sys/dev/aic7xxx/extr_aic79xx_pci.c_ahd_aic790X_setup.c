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
typedef  scalar_t__ u_int ;
struct ahd_softc {int bugs; int flags; int features; scalar_t__ channel; int /*<<< orphan*/  dev_softc; } ;
typedef  int /*<<< orphan*/  aic_dev_softc_t ;

/* Variables and functions */
 int AHD_ABORT_LQI_BUG ; 
 int /*<<< orphan*/  AHD_AMPLITUDE_DEF ; 
 int AHD_AUTOFLUSH_BUG ; 
 int AHD_BUSFREEREV_BUG ; 
 int AHD_CLRLQO_AUTOCLR_BUG ; 
 int AHD_EARLY_REQ_BUG ; 
 int AHD_FAINT_LED_BUG ; 
 int AHD_FAST_CDB_DELIVERY ; 
 int AHD_HP_BOARD ; 
 int AHD_INTCOLLISION_BUG ; 
 int AHD_LONG_SETIMO_BUG ; 
 int AHD_LQOOVERRUN_BUG ; 
 int AHD_LQO_ATNO_BUG ; 
 int AHD_MDFF_WSCBPTR_BUG ; 
 int AHD_MULTI_FUNC ; 
 int AHD_NEW_DFCNTRL_OPTS ; 
 int AHD_NEW_IOCELL_OPTS ; 
 int AHD_NLQICRC_DELAYED_BUG ; 
 int AHD_NONPACKFIFO_BUG ; 
 int AHD_PACED_NEGTABLE_BUG ; 
 int AHD_PCIX_CHIPRST_BUG ; 
 int AHD_PCIX_MMAPIO_BUG ; 
 int AHD_PCIX_SCBRAM_RD_BUG ; 
 int AHD_PKTIZED_STATUS_BUG ; 
 int AHD_PKT_BITBUCKET_BUG ; 
 int AHD_PKT_LUN_BUG ; 
 int /*<<< orphan*/  AHD_PRECOMP_CUTBACK_29 ; 
 int AHD_REG_SLOW_SETTLE_BUG ; 
 int AHD_RTI ; 
 int AHD_SCSIRST_BUG ; 
 int AHD_SENT_SCB_UPDATE_BUG ; 
 int /*<<< orphan*/  AHD_SET_AMPLITUDE (struct ahd_softc*,int /*<<< orphan*/ ) ; 
 int AHD_SET_MODE_BUG ; 
 int /*<<< orphan*/  AHD_SET_PRECOMP (struct ahd_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AHD_SET_SLEWRATE (struct ahd_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AHD_SLEWRATE_DEF_REVA ; 
 int /*<<< orphan*/  AHD_SLEWRATE_DEF_REVB ; 
 int /*<<< orphan*/  DEVCONFIG1 ; 
 int ENXIO ; 
 scalar_t__ ID_AIC7902_PCI_REV_A4 ; 
 scalar_t__ ID_AIC7902_PCI_REV_B0 ; 
 int /*<<< orphan*/  PCIR_COMMAND ; 
 int /*<<< orphan*/  PCIR_REVID ; 
 scalar_t__ PREQDIS ; 
 char* ahd_name (struct ahd_softc*) ; 
 scalar_t__ aic_get_pci_function (int /*<<< orphan*/ ) ; 
 scalar_t__ aic_pci_read_config (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  aic_pci_write_config (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  printf (char*,char*,scalar_t__) ; 

__attribute__((used)) static int
ahd_aic790X_setup(struct ahd_softc *ahd)
{
	aic_dev_softc_t pci;
	u_int rev;

	pci = ahd->dev_softc;
	rev = aic_pci_read_config(pci, PCIR_REVID, /*bytes*/1);
	if (rev < ID_AIC7902_PCI_REV_A4) {
		printf("%s: Unable to attach to unsupported chip revision %d\n",
		       ahd_name(ahd), rev);
		aic_pci_write_config(pci, PCIR_COMMAND, 0, /*bytes*/2);
		return (ENXIO);
	}
	ahd->channel = aic_get_pci_function(pci) + 'A';
	if (rev < ID_AIC7902_PCI_REV_B0) {
		/*
		 * Enable A series workarounds.
		 */
		ahd->bugs |= AHD_SENT_SCB_UPDATE_BUG|AHD_ABORT_LQI_BUG
			  |  AHD_PKT_BITBUCKET_BUG|AHD_LONG_SETIMO_BUG
			  |  AHD_NLQICRC_DELAYED_BUG|AHD_SCSIRST_BUG
			  |  AHD_LQO_ATNO_BUG|AHD_AUTOFLUSH_BUG
			  |  AHD_CLRLQO_AUTOCLR_BUG|AHD_PCIX_MMAPIO_BUG
			  |  AHD_PCIX_CHIPRST_BUG|AHD_PCIX_SCBRAM_RD_BUG
			  |  AHD_PKTIZED_STATUS_BUG|AHD_PKT_LUN_BUG
			  |  AHD_MDFF_WSCBPTR_BUG|AHD_REG_SLOW_SETTLE_BUG
			  |  AHD_SET_MODE_BUG|AHD_BUSFREEREV_BUG
			  |  AHD_NONPACKFIFO_BUG|AHD_PACED_NEGTABLE_BUG
			  |  AHD_FAINT_LED_BUG;

		/*
		 * IO Cell parameter setup.
		 */
		AHD_SET_PRECOMP(ahd, AHD_PRECOMP_CUTBACK_29);

		if ((ahd->flags & AHD_HP_BOARD) == 0)
			AHD_SET_SLEWRATE(ahd, AHD_SLEWRATE_DEF_REVA);
	} else {
		u_int devconfig1;

		ahd->features |= AHD_RTI|AHD_NEW_IOCELL_OPTS
			      |  AHD_NEW_DFCNTRL_OPTS|AHD_FAST_CDB_DELIVERY;
		ahd->bugs |= AHD_LQOOVERRUN_BUG|AHD_EARLY_REQ_BUG;

		/*
		 * Some issues have been resolved in the 7901B.
		 */
		if ((ahd->features & AHD_MULTI_FUNC) != 0)
			ahd->bugs |= AHD_INTCOLLISION_BUG|AHD_ABORT_LQI_BUG
				  |  AHD_BUSFREEREV_BUG;

		/*
		 * IO Cell parameter setup.
		 */
		AHD_SET_PRECOMP(ahd, AHD_PRECOMP_CUTBACK_29);
		AHD_SET_SLEWRATE(ahd, AHD_SLEWRATE_DEF_REVB);
		AHD_SET_AMPLITUDE(ahd, AHD_AMPLITUDE_DEF);

		/*
		 * Set the PREQDIS bit for H2B which disables some workaround
		 * that doesn't work on regular PCI busses.
		 * XXX - Find out exactly what this does from the hardware
		 * 	 folks!
		 */
		devconfig1 = aic_pci_read_config(pci, DEVCONFIG1, /*bytes*/1);
		aic_pci_write_config(pci, DEVCONFIG1,
				     devconfig1|PREQDIS, /*bytes*/1);
		devconfig1 = aic_pci_read_config(pci, DEVCONFIG1, /*bytes*/1);
	}

	return (0);
}