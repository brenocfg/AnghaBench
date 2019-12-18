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
struct ahd_softc {int /*<<< orphan*/  flags; int /*<<< orphan*/  reset_timer; } ;

/* Variables and functions */
 int /*<<< orphan*/  AHD_MODE_SCSI ; 
 int /*<<< orphan*/  AHD_RESET_POLL_ACTIVE ; 
 int /*<<< orphan*/  AHD_RESET_POLL_MS ; 
 int CLRSCSIRSTI ; 
 int /*<<< orphan*/  CLRSINT1 ; 
 int ENAUTOATNP ; 
 int ENRSELI ; 
 int ENSCSIRST ; 
 int ENSELI ; 
 int SCSIRSTI ; 
 int /*<<< orphan*/  SCSISEQ1 ; 
 int /*<<< orphan*/  SCSISEQ_TEMPLATE ; 
 int /*<<< orphan*/  SIMODE1 ; 
 int /*<<< orphan*/  SSTAT1 ; 
 int ahd_inb (struct ahd_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ahd_lock (struct ahd_softc*) ; 
 int /*<<< orphan*/  ahd_outb (struct ahd_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ahd_pause (struct ahd_softc*) ; 
 int /*<<< orphan*/  ahd_set_modes (struct ahd_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ahd_unlock (struct ahd_softc*) ; 
 int /*<<< orphan*/  ahd_unpause (struct ahd_softc*) ; 
 int /*<<< orphan*/  ahd_update_modes (struct ahd_softc*) ; 
 int /*<<< orphan*/  aic_release_simq (struct ahd_softc*) ; 
 int /*<<< orphan*/  aic_timer_reset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void (*) (void*),struct ahd_softc*) ; 

__attribute__((used)) static void
ahd_reset_poll(void *arg)
{
	struct	ahd_softc *ahd = (struct ahd_softc *)arg;
	u_int	scsiseq1;
	
	ahd_lock(ahd);
	ahd_pause(ahd);
	ahd_update_modes(ahd);
	ahd_set_modes(ahd, AHD_MODE_SCSI, AHD_MODE_SCSI);
	ahd_outb(ahd, CLRSINT1, CLRSCSIRSTI);
	if ((ahd_inb(ahd, SSTAT1) & SCSIRSTI) != 0) {
		aic_timer_reset(&ahd->reset_timer, AHD_RESET_POLL_MS,
				ahd_reset_poll, ahd);
		ahd_unpause(ahd);
		ahd_unlock(ahd);
		return;
	}

	/* Reset is now low.  Complete chip reinitialization. */
	ahd_outb(ahd, SIMODE1, ahd_inb(ahd, SIMODE1) | ENSCSIRST);
	scsiseq1 = ahd_inb(ahd, SCSISEQ_TEMPLATE);
	ahd_outb(ahd, SCSISEQ1, scsiseq1 & (ENSELI|ENRSELI|ENAUTOATNP));
	ahd_unpause(ahd);
	ahd->flags &= ~AHD_RESET_POLL_ACTIVE;
	aic_release_simq(ahd);
	ahd_unlock(ahd);
}