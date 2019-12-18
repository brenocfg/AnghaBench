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
typedef  int u_int ;
struct ahd_softc {int /*<<< orphan*/  dev_softc; } ;
typedef  int /*<<< orphan*/  ahd_mode_state ;

/* Variables and functions */
 int /*<<< orphan*/  AHD_MODE_CFG ; 
 int CLRINT ; 
 int CLRPCIINT ; 
 int DF0PCISTAT ; 
 int INTSTAT ; 
 int PCIINT ; 
 scalar_t__ PCIR_STATUS ; 
 int SPLTINT ; 
 int /*<<< orphan*/  ahd_dump_card_state (struct ahd_softc*) ; 
 int ahd_inb (struct ahd_softc*,int) ; 
 char* ahd_name (struct ahd_softc*) ; 
 int /*<<< orphan*/  ahd_outb (struct ahd_softc*,int,int) ; 
 int /*<<< orphan*/  ahd_pci_split_intr (struct ahd_softc*,int) ; 
 int /*<<< orphan*/  ahd_restore_modes (struct ahd_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ahd_save_modes (struct ahd_softc*) ; 
 int /*<<< orphan*/  ahd_set_modes (struct ahd_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ahd_unpause (struct ahd_softc*) ; 
 int aic_pci_read_config (int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  aic_pci_write_config (int /*<<< orphan*/ ,scalar_t__,int,int) ; 
 int /*<<< orphan*/ * pci_status_source ; 
 char** pci_status_strings ; 
 int /*<<< orphan*/  printf (char const*,char*,...) ; 

void
ahd_pci_intr(struct ahd_softc *ahd)
{
	uint8_t		pci_status[8];
	ahd_mode_state	saved_modes;
	u_int		pci_status1;
	u_int		intstat;
	u_int		i;
	u_int		reg;
	
	intstat = ahd_inb(ahd, INTSTAT);

	if ((intstat & SPLTINT) != 0)
		ahd_pci_split_intr(ahd, intstat);

	if ((intstat & PCIINT) == 0)
		return;

	printf("%s: PCI error Interrupt\n", ahd_name(ahd));
	saved_modes = ahd_save_modes(ahd);
	ahd_dump_card_state(ahd);
	ahd_set_modes(ahd, AHD_MODE_CFG, AHD_MODE_CFG);
	for (i = 0, reg = DF0PCISTAT; i < 8; i++, reg++) {

		if (i == 5)
			continue;
		pci_status[i] = ahd_inb(ahd, reg);
		/* Clear latched errors.  So our interrupt deasserts. */
		ahd_outb(ahd, reg, pci_status[i]);
	}

	for (i = 0; i < 8; i++) {
		u_int bit;
	
		if (i == 5)
			continue;

		for (bit = 0; bit < 8; bit++) {

			if ((pci_status[i] & (0x1 << bit)) != 0) {
				static const char *s;

				s = pci_status_strings[bit];
				if (i == 7/*TARG*/ && bit == 3)
					s = "%s: Signaled Target Abort\n";
				printf(s, ahd_name(ahd), pci_status_source[i]);
			}
		}	
	}
	pci_status1 = aic_pci_read_config(ahd->dev_softc,
					  PCIR_STATUS + 1, /*bytes*/1);
	aic_pci_write_config(ahd->dev_softc, PCIR_STATUS + 1,
			     pci_status1, /*bytes*/1);
	ahd_restore_modes(ahd, saved_modes);
	ahd_outb(ahd, CLRINT, CLRPCIINT);
	ahd_unpause(ahd);
}