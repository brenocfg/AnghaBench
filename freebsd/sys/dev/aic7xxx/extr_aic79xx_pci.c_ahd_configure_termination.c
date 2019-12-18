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
typedef  int uint8_t ;
typedef  int uint32_t ;
typedef  int u_int ;
struct ahd_softc {int flags; int /*<<< orphan*/  dev_softc; } ;

/* Variables and functions */
 int AHD_CURRENT_SENSING ; 
 int AHD_STPWLEVEL_A ; 
 int AHD_TERM_ENB_A ; 
 int CFAUTOTERM ; 
 int CFSEAUTOTERM ; 
 int CFSEHIGHTERM ; 
 int CFSELOWTERM ; 
 int CFSTERM ; 
 int CFWSTERM ; 
 int /*<<< orphan*/  DEVCONFIG ; 
 int /*<<< orphan*/  FLXADDR_ROMSTAT_CURSENSECTL ; 
 int /*<<< orphan*/  FLXADDR_TERMCTL ; 
 int FLX_TERMCTL_ENPRIHIGH ; 
 int FLX_TERMCTL_ENPRILOW ; 
 int FLX_TERMCTL_ENSECHIGH ; 
 int FLX_TERMCTL_ENSECLOW ; 
 int STPWEN ; 
 int STPWLEVEL ; 
 int /*<<< orphan*/  SXFRCTL1 ; 
 int ahd_inb (struct ahd_softc*,int /*<<< orphan*/ ) ; 
 char* ahd_name (struct ahd_softc*) ; 
 int /*<<< orphan*/  ahd_outb (struct ahd_softc*,int /*<<< orphan*/ ,int) ; 
 int ahd_read_flexport (struct ahd_softc*,int /*<<< orphan*/ ,int*) ; 
 int ahd_write_flexport (struct ahd_softc*,int /*<<< orphan*/ ,int) ; 
 int aic_pci_read_config (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  aic_pci_write_config (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 scalar_t__ bootverbose ; 
 int /*<<< orphan*/  printf (char*,char*,...) ; 

__attribute__((used)) static void
ahd_configure_termination(struct ahd_softc *ahd, u_int adapter_control)
{
	int	 error;
	u_int	 sxfrctl1;
	uint8_t	 termctl;
	uint32_t devconfig;

	devconfig = aic_pci_read_config(ahd->dev_softc, DEVCONFIG, /*bytes*/4);
	devconfig &= ~STPWLEVEL;
	if ((ahd->flags & AHD_STPWLEVEL_A) != 0)
		devconfig |= STPWLEVEL;
	if (bootverbose)
		printf("%s: STPWLEVEL is %s\n",
		       ahd_name(ahd), (devconfig & STPWLEVEL) ? "on" : "off");
	aic_pci_write_config(ahd->dev_softc, DEVCONFIG, devconfig, /*bytes*/4);
 
	/* Make sure current sensing is off. */
	if ((ahd->flags & AHD_CURRENT_SENSING) != 0) {
		(void)ahd_write_flexport(ahd, FLXADDR_ROMSTAT_CURSENSECTL, 0);
	}

	/*
	 * Read to sense.  Write to set.
	 */
	error = ahd_read_flexport(ahd, FLXADDR_TERMCTL, &termctl);
	if ((adapter_control & CFAUTOTERM) == 0) {
		if (bootverbose)
			printf("%s: Manual Primary Termination\n",
			       ahd_name(ahd));
		termctl &= ~(FLX_TERMCTL_ENPRILOW|FLX_TERMCTL_ENPRIHIGH);
		if ((adapter_control & CFSTERM) != 0)
			termctl |= FLX_TERMCTL_ENPRILOW;
		if ((adapter_control & CFWSTERM) != 0)
			termctl |= FLX_TERMCTL_ENPRIHIGH;
	} else if (error != 0) {
		printf("%s: Primary Auto-Term Sensing failed! "
		       "Using Defaults.\n", ahd_name(ahd));
		termctl = FLX_TERMCTL_ENPRILOW|FLX_TERMCTL_ENPRIHIGH;
	}

	if ((adapter_control & CFSEAUTOTERM) == 0) {
		if (bootverbose)
			printf("%s: Manual Secondary Termination\n",
			       ahd_name(ahd));
		termctl &= ~(FLX_TERMCTL_ENSECLOW|FLX_TERMCTL_ENSECHIGH);
		if ((adapter_control & CFSELOWTERM) != 0)
			termctl |= FLX_TERMCTL_ENSECLOW;
		if ((adapter_control & CFSEHIGHTERM) != 0)
			termctl |= FLX_TERMCTL_ENSECHIGH;
	} else if (error != 0) {
		printf("%s: Secondary Auto-Term Sensing failed! "
		       "Using Defaults.\n", ahd_name(ahd));
		termctl |= FLX_TERMCTL_ENSECLOW|FLX_TERMCTL_ENSECHIGH;
	}

	/*
	 * Now set the termination based on what we found.
	 */
	sxfrctl1 = ahd_inb(ahd, SXFRCTL1) & ~STPWEN;
	ahd->flags &= ~AHD_TERM_ENB_A;
	if ((termctl & FLX_TERMCTL_ENPRILOW) != 0) {
		ahd->flags |= AHD_TERM_ENB_A;
		sxfrctl1 |= STPWEN;
	}
	/* Must set the latch once in order to be effective. */
	ahd_outb(ahd, SXFRCTL1, sxfrctl1|STPWEN);
	ahd_outb(ahd, SXFRCTL1, sxfrctl1);

	error = ahd_write_flexport(ahd, FLXADDR_TERMCTL, termctl);
	if (error != 0) {
		printf("%s: Unable to set termination settings!\n",
		       ahd_name(ahd));
	} else if (bootverbose) {
		printf("%s: Primary High byte termination %sabled\n",
		       ahd_name(ahd),
		       (termctl & FLX_TERMCTL_ENPRIHIGH) ? "En" : "Dis");

		printf("%s: Primary Low byte termination %sabled\n",
		       ahd_name(ahd),
		       (termctl & FLX_TERMCTL_ENPRILOW) ? "En" : "Dis");

		printf("%s: Secondary High byte termination %sabled\n",
		       ahd_name(ahd),
		       (termctl & FLX_TERMCTL_ENSECHIGH) ? "En" : "Dis");

		printf("%s: Secondary Low byte termination %sabled\n",
		       ahd_name(ahd),
		       (termctl & FLX_TERMCTL_ENSECLOW) ? "En" : "Dis");
	}
	return;
}