#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_int ;
struct seeprom_descriptor {void* sd_dataout_offset; void* sd_status_offset; void* sd_control_offset; struct ahc_softc* sd_ahc; } ;
struct TYPE_4__ {int /*<<< orphan*/  csize_lattime; int /*<<< orphan*/  command; int /*<<< orphan*/  devconfig; } ;
struct TYPE_5__ {TYPE_1__ pci_softc; } ;
struct ahc_softc {int flags; TYPE_3__* seep_config; TYPE_2__ bus_softc; int /*<<< orphan*/  dev_softc; } ;
struct TYPE_6__ {int /*<<< orphan*/  adapter_control; } ;

/* Variables and functions */
 int AHC_HAS_TERM_LOGIC ; 
 int /*<<< orphan*/  AIC_POWER_STATE_D0 ; 
 int /*<<< orphan*/  CSIZE_LATTIME ; 
 int /*<<< orphan*/  DEVCONFIG ; 
 int /*<<< orphan*/  PCIR_COMMAND ; 
 void* SEECTL ; 
 int /*<<< orphan*/  ahc_acquire_seeprom (struct ahc_softc*,struct seeprom_descriptor*) ; 
 int /*<<< orphan*/  ahc_release_seeprom (struct seeprom_descriptor*) ; 
 int ahc_resume (struct ahc_softc*) ; 
 int /*<<< orphan*/  aic_pci_write_config (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  aic_power_state_change (struct ahc_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  configure_termination (struct ahc_softc*,struct seeprom_descriptor*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
ahc_pci_resume(struct ahc_softc *ahc)
{

	aic_power_state_change(ahc, AIC_POWER_STATE_D0);

	/*
	 * We assume that the OS has restored our register
	 * mappings, etc.  Just update the config space registers
	 * that the OS doesn't know about and rely on our chip
	 * reset handler to handle the rest.
	 */
	aic_pci_write_config(ahc->dev_softc, DEVCONFIG,
			     ahc->bus_softc.pci_softc.devconfig, /*bytes*/4);
	aic_pci_write_config(ahc->dev_softc, PCIR_COMMAND,
			     ahc->bus_softc.pci_softc.command, /*bytes*/1);
	aic_pci_write_config(ahc->dev_softc, CSIZE_LATTIME,
			     ahc->bus_softc.pci_softc.csize_lattime,
			     /*bytes*/1);
	if ((ahc->flags & AHC_HAS_TERM_LOGIC) != 0) {
		struct	seeprom_descriptor sd;
		u_int	sxfrctl1;

		sd.sd_ahc = ahc;
		sd.sd_control_offset = SEECTL;		
		sd.sd_status_offset = SEECTL;		
		sd.sd_dataout_offset = SEECTL;		

		ahc_acquire_seeprom(ahc, &sd);
		configure_termination(ahc, &sd,
				      ahc->seep_config->adapter_control,
				      &sxfrctl1);
		ahc_release_seeprom(&sd);
	}
	return (ahc_resume(ahc));
}