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
struct ahd_softc {scalar_t__ saved_src_mode; scalar_t__ saved_dst_mode; int flags; int /*<<< orphan*/  unpause; } ;

/* Variables and functions */
 scalar_t__ AHD_MODE_UNKNOWN ; 
 int AHD_UPDATE_PEND_CMDS ; 
 int CMDCMPLT ; 
 int /*<<< orphan*/  HCNTRL ; 
 int /*<<< orphan*/  INTSTAT ; 
 int ahd_inb (struct ahd_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ahd_known_modes (struct ahd_softc*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  ahd_outb (struct ahd_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ahd_reset_cmds_pending (struct ahd_softc*) ; 
 int /*<<< orphan*/  ahd_set_modes (struct ahd_softc*,scalar_t__,scalar_t__) ; 

__attribute__((used)) static __inline void
ahd_unpause(struct ahd_softc *ahd)
{
	/*
	 * Automatically restore our modes to those saved
	 * prior to the first change of the mode.
	 */
	if (ahd->saved_src_mode != AHD_MODE_UNKNOWN
	 && ahd->saved_dst_mode != AHD_MODE_UNKNOWN) {
		if ((ahd->flags & AHD_UPDATE_PEND_CMDS) != 0)
			ahd_reset_cmds_pending(ahd);
		ahd_set_modes(ahd, ahd->saved_src_mode, ahd->saved_dst_mode);
	}

	if ((ahd_inb(ahd, INTSTAT) & ~CMDCMPLT) == 0)
		ahd_outb(ahd, HCNTRL, ahd->unpause);

	ahd_known_modes(ahd, AHD_MODE_UNKNOWN, AHD_MODE_UNKNOWN);
}