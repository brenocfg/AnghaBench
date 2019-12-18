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
struct ahc_softc {int features; } ;
struct ahc_devinfo {int dummy; } ;
typedef  scalar_t__ role_t ;

/* Variables and functions */
 int AHC_MULTI_TID ; 
 int AHC_ULTRA2 ; 
 int CMDPHASE_PENDING ; 
 int NO_DISCONNECT ; 
 int OID ; 
 scalar_t__ ROLE_INITIATOR ; 
 scalar_t__ ROLE_TARGET ; 
 int /*<<< orphan*/  SAVED_LUN ; 
 int /*<<< orphan*/  SAVED_SCSIID ; 
 int /*<<< orphan*/  SCSIID ; 
 int /*<<< orphan*/  SCSIID_CHANNEL (struct ahc_softc*,int) ; 
 int /*<<< orphan*/  SCSIID_TARGET (struct ahc_softc*,int) ; 
 int /*<<< orphan*/  SCSIID_ULTRA2 ; 
 int /*<<< orphan*/  SEQ_FLAGS ; 
 int /*<<< orphan*/  SSTAT0 ; 
 int TARGET ; 
 int /*<<< orphan*/  TARGIDIN ; 
 int TARG_CMD_PENDING ; 
 int /*<<< orphan*/  ahc_compile_devinfo (struct ahc_devinfo*,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,scalar_t__) ; 
 int ahc_inb (struct ahc_softc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ahc_fetch_devinfo(struct ahc_softc *ahc, struct ahc_devinfo *devinfo)
{
	u_int	saved_scsiid;
	role_t	role;
	int	our_id;

	if (ahc_inb(ahc, SSTAT0) & TARGET)
		role = ROLE_TARGET;
	else
		role = ROLE_INITIATOR;

	if (role == ROLE_TARGET
	 && (ahc->features & AHC_MULTI_TID) != 0
	 && (ahc_inb(ahc, SEQ_FLAGS)
 	   & (CMDPHASE_PENDING|TARG_CMD_PENDING|NO_DISCONNECT)) != 0) {
		/* We were selected, so pull our id from TARGIDIN */
		our_id = ahc_inb(ahc, TARGIDIN) & OID;
	} else if ((ahc->features & AHC_ULTRA2) != 0)
		our_id = ahc_inb(ahc, SCSIID_ULTRA2) & OID;
	else
		our_id = ahc_inb(ahc, SCSIID) & OID;

	saved_scsiid = ahc_inb(ahc, SAVED_SCSIID);
	ahc_compile_devinfo(devinfo,
			    our_id,
			    SCSIID_TARGET(ahc, saved_scsiid),
			    ahc_inb(ahc, SAVED_LUN),
			    SCSIID_CHANNEL(ahc, saved_scsiid),
			    role);
}