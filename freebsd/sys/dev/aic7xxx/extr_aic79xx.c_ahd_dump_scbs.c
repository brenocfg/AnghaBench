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
typedef  int u_int ;
struct ahd_softc {int dummy; } ;
typedef  int /*<<< orphan*/  ahd_mode_state ;

/* Variables and functions */
 int /*<<< orphan*/  AHD_MODE_SCSI ; 
 int AHD_SCB_MAX ; 
 int /*<<< orphan*/  SCB_CONTROL ; 
 int /*<<< orphan*/  SCB_NEXT ; 
 int /*<<< orphan*/  SCB_NEXT2 ; 
 int /*<<< orphan*/  SCB_RESIDUAL_SGPTR ; 
 int /*<<< orphan*/  SCB_SCSIID ; 
 int /*<<< orphan*/  SCB_SGPTR ; 
 int ahd_get_scbptr (struct ahd_softc*) ; 
 int ahd_inb_scbram (struct ahd_softc*,int /*<<< orphan*/ ) ; 
 int ahd_inl_scbram (struct ahd_softc*,int /*<<< orphan*/ ) ; 
 int ahd_inw_scbram (struct ahd_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ahd_restore_modes (struct ahd_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ahd_save_modes (struct ahd_softc*) ; 
 int /*<<< orphan*/  ahd_set_modes (struct ahd_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ahd_set_scbptr (struct ahd_softc*,int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

void
ahd_dump_scbs(struct ahd_softc *ahd)
{
	ahd_mode_state saved_modes;
	u_int	       saved_scb_index;
	int	       i;

	saved_modes = ahd_save_modes(ahd);
	ahd_set_modes(ahd, AHD_MODE_SCSI, AHD_MODE_SCSI);
	saved_scb_index = ahd_get_scbptr(ahd);
	for (i = 0; i < AHD_SCB_MAX; i++) {
		ahd_set_scbptr(ahd, i);
		printf("%3d", i);
		printf("(CTRL 0x%x ID 0x%x N 0x%x N2 0x%x SG 0x%x, RSG 0x%x)\n",
		       ahd_inb_scbram(ahd, SCB_CONTROL),
		       ahd_inb_scbram(ahd, SCB_SCSIID),
		       ahd_inw_scbram(ahd, SCB_NEXT),
		       ahd_inw_scbram(ahd, SCB_NEXT2),
		       ahd_inl_scbram(ahd, SCB_SGPTR),
		       ahd_inl_scbram(ahd, SCB_RESIDUAL_SGPTR));
	}
	printf("\n");
	ahd_set_scbptr(ahd, saved_scb_index);
	ahd_restore_modes(ahd, saved_modes);
}