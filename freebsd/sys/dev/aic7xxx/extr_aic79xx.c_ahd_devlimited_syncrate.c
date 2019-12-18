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
struct ahd_transinfo {int ppr_options; scalar_t__ width; scalar_t__ period; } ;
struct ahd_softc {int dummy; } ;
struct ahd_initiator_tinfo {struct ahd_transinfo goal; struct ahd_transinfo user; } ;
typedef  scalar_t__ role_t ;

/* Variables and functions */
 int AHD_SYNCRATE_PACED ; 
 int AHD_SYNCRATE_ULTRA ; 
 scalar_t__ AHD_SYNCRATE_ULTRA2 ; 
 int ENAB40 ; 
 int EXP_ACTIVE ; 
 int MAX (int,scalar_t__) ; 
 int MSG_EXT_PPR_DT_REQ ; 
 int MSG_EXT_PPR_PCOMP_EN ; 
 int MSG_EXT_PPR_QAS_REQ ; 
 scalar_t__ MSG_EXT_WDTR_BUS_8_BIT ; 
 scalar_t__ ROLE_TARGET ; 
 int /*<<< orphan*/  SBLKCTL ; 
 int /*<<< orphan*/  SSTAT2 ; 
 int /*<<< orphan*/  ahd_find_syncrate (struct ahd_softc*,int*,int*,int) ; 
 int ahd_inb (struct ahd_softc*,int /*<<< orphan*/ ) ; 

void
ahd_devlimited_syncrate(struct ahd_softc *ahd,
			struct ahd_initiator_tinfo *tinfo,
			u_int *period, u_int *ppr_options, role_t role)
{
	struct	ahd_transinfo *transinfo;
	u_int	maxsync;

	if ((ahd_inb(ahd, SBLKCTL) & ENAB40) != 0
	 && (ahd_inb(ahd, SSTAT2) & EXP_ACTIVE) == 0) {
		maxsync = AHD_SYNCRATE_PACED;
	} else {
		maxsync = AHD_SYNCRATE_ULTRA;
		/* Can't do DT related options on an SE bus */
		*ppr_options &= MSG_EXT_PPR_QAS_REQ;
	}
	/*
	 * Never allow a value higher than our current goal
	 * period otherwise we may allow a target initiated
	 * negotiation to go above the limit as set by the
	 * user.  In the case of an initiator initiated
	 * sync negotiation, we limit based on the user
	 * setting.  This allows the system to still accept
	 * incoming negotiations even if target initiated
	 * negotiation is not performed.
	 */
	if (role == ROLE_TARGET)
		transinfo = &tinfo->user;
	else 
		transinfo = &tinfo->goal;
	*ppr_options &= (transinfo->ppr_options|MSG_EXT_PPR_PCOMP_EN);
	if (transinfo->width == MSG_EXT_WDTR_BUS_8_BIT) {
		maxsync = MAX(maxsync, AHD_SYNCRATE_ULTRA2);
		*ppr_options &= ~MSG_EXT_PPR_DT_REQ;
	}
	if (transinfo->period == 0) {
		*period = 0;
		*ppr_options = 0;
	} else {
		*period = MAX(*period, transinfo->period);
		ahd_find_syncrate(ahd, period, ppr_options, maxsync);
	}
}