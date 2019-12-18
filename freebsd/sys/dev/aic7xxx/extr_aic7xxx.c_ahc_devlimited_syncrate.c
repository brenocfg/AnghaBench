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
typedef  int /*<<< orphan*/  u_int ;
struct ahc_transinfo {scalar_t__ width; scalar_t__ period; int /*<<< orphan*/  ppr_options; } ;
struct ahc_syncrate {int dummy; } ;
struct ahc_softc {int features; } ;
struct ahc_initiator_tinfo {struct ahc_transinfo goal; struct ahc_transinfo user; } ;
typedef  scalar_t__ role_t ;

/* Variables and functions */
 int /*<<< orphan*/  AHC_SYNCRATE_DT ; 
 int /*<<< orphan*/  AHC_SYNCRATE_FAST ; 
 int /*<<< orphan*/  AHC_SYNCRATE_ULTRA ; 
 scalar_t__ AHC_SYNCRATE_ULTRA2 ; 
 int AHC_ULTRA ; 
 int AHC_ULTRA2 ; 
 int ENAB40 ; 
 int EXP_ACTIVE ; 
 int /*<<< orphan*/  MAX (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  MSG_EXT_PPR_DT_REQ ; 
 scalar_t__ MSG_EXT_WDTR_BUS_8_BIT ; 
 scalar_t__ ROLE_TARGET ; 
 int /*<<< orphan*/  SBLKCTL ; 
 int /*<<< orphan*/  SSTAT2 ; 
 struct ahc_syncrate* ahc_find_syncrate (struct ahc_softc*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int ahc_inb (struct ahc_softc*,int /*<<< orphan*/ ) ; 

struct ahc_syncrate *
ahc_devlimited_syncrate(struct ahc_softc *ahc,
			struct ahc_initiator_tinfo *tinfo,
			u_int *period, u_int *ppr_options, role_t role)
{
	struct	ahc_transinfo *transinfo;
	u_int	maxsync;

	if ((ahc->features & AHC_ULTRA2) != 0) {
		if ((ahc_inb(ahc, SBLKCTL) & ENAB40) != 0
		 && (ahc_inb(ahc, SSTAT2) & EXP_ACTIVE) == 0) {
			maxsync = AHC_SYNCRATE_DT;
		} else {
			maxsync = AHC_SYNCRATE_ULTRA;
			/* Can't do DT on an SE bus */
			*ppr_options &= ~MSG_EXT_PPR_DT_REQ;
		}
	} else if ((ahc->features & AHC_ULTRA) != 0) {
		maxsync = AHC_SYNCRATE_ULTRA;
	} else {
		maxsync = AHC_SYNCRATE_FAST;
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
	*ppr_options &= transinfo->ppr_options;
	if (transinfo->width == MSG_EXT_WDTR_BUS_8_BIT) {
		maxsync = MAX(maxsync, AHC_SYNCRATE_ULTRA2);
		*ppr_options &= ~MSG_EXT_PPR_DT_REQ;
	}
	if (transinfo->period == 0) {
		*period = 0;
		*ppr_options = 0;
		return (NULL);
	}
	*period = MAX(*period, transinfo->period);
	return (ahc_find_syncrate(ahc, period, ppr_options, maxsync));
}