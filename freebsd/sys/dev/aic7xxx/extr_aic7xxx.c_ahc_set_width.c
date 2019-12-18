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
typedef  int u_int ;
struct ahc_tmode_tstate {int dummy; } ;
struct ahc_softc {int dummy; } ;
struct TYPE_6__ {int width; } ;
struct TYPE_5__ {int width; } ;
struct TYPE_4__ {int width; } ;
struct ahc_initiator_tinfo {int scsirate; TYPE_3__ curr; TYPE_2__ goal; TYPE_1__ user; } ;
struct ahc_devinfo {int target; int /*<<< orphan*/  channel; int /*<<< orphan*/  our_scsiid; } ;

/* Variables and functions */
 int /*<<< orphan*/  AC_TRANSFER_NEG ; 
 int /*<<< orphan*/  AHC_NEG_TO_GOAL ; 
 int AHC_TRANS_ACTIVE ; 
 int AHC_TRANS_CUR ; 
 int AHC_TRANS_GOAL ; 
 int AHC_TRANS_USER ; 
 int /*<<< orphan*/  CAM_LUN_WILDCARD ; 
 int MSG_EXT_WDTR_BUS_16_BIT ; 
 int /*<<< orphan*/  SCSIRATE ; 
 int WIDEXFER ; 
 struct ahc_initiator_tinfo* ahc_fetch_transinfo (struct ahc_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct ahc_tmode_tstate**) ; 
 char* ahc_name (struct ahc_softc*) ; 
 int /*<<< orphan*/  ahc_outb (struct ahc_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ahc_send_async (struct ahc_softc*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ ahc_update_neg_request (struct ahc_softc*,struct ahc_devinfo*,struct ahc_tmode_tstate*,struct ahc_initiator_tinfo*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ahc_update_pending_scbs (struct ahc_softc*) ; 
 scalar_t__ bootverbose ; 
 int /*<<< orphan*/  printf (char*,char*,int,int) ; 

void
ahc_set_width(struct ahc_softc *ahc, struct ahc_devinfo *devinfo,
	      u_int width, u_int type, int paused)
{
	struct	ahc_initiator_tinfo *tinfo;
	struct	ahc_tmode_tstate *tstate;
	u_int	oldwidth;
	int	active;
	int	update_needed;

	active = (type & AHC_TRANS_ACTIVE) == AHC_TRANS_ACTIVE;
	update_needed = 0;
	tinfo = ahc_fetch_transinfo(ahc, devinfo->channel, devinfo->our_scsiid,
				    devinfo->target, &tstate);

	if ((type & AHC_TRANS_USER) != 0)
		tinfo->user.width = width;

	if ((type & AHC_TRANS_GOAL) != 0)
		tinfo->goal.width = width;

	oldwidth = tinfo->curr.width;
	if ((type & AHC_TRANS_CUR) != 0 && oldwidth != width) {
		u_int	scsirate;

		update_needed++;
		scsirate =  tinfo->scsirate;
		scsirate &= ~WIDEXFER;
		if (width == MSG_EXT_WDTR_BUS_16_BIT)
			scsirate |= WIDEXFER;

		tinfo->scsirate = scsirate;

		if (active)
			ahc_outb(ahc, SCSIRATE, scsirate);

		tinfo->curr.width = width;

		ahc_send_async(ahc, devinfo->channel, devinfo->target,
			       CAM_LUN_WILDCARD, AC_TRANSFER_NEG, NULL);
		if (bootverbose) {
			printf("%s: target %d using %dbit transfers\n",
			       ahc_name(ahc), devinfo->target,
			       8 * (0x01 << width));
		}
	}

	update_needed += ahc_update_neg_request(ahc, devinfo, tstate,
						tinfo, AHC_NEG_TO_GOAL);
	if (update_needed)
		ahc_update_pending_scbs(ahc);
}