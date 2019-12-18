#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int flags; } ;
struct TYPE_8__ {TYPE_3__ cmd; } ;
struct TYPE_6__ {int target_id; scalar_t__ func_code; } ;
union ccb {TYPE_4__ ataio; TYPE_2__ ccb_h; } ;
struct fsl_sata_channel {int oslots; scalar_t__* numrslotspd; scalar_t__* numtslotspd; scalar_t__ numrslots; scalar_t__ aslots; TYPE_1__* curr; } ;
struct TYPE_5__ {int tags; } ;

/* Variables and functions */
 int CAM_ATAIO_CONTROL ; 
 int CAM_ATAIO_FPDMA ; 
 int CAM_ATAIO_NEEDRESULT ; 
 scalar_t__ XPT_ATA_IO ; 

__attribute__((used)) static int
fsl_sata_check_collision(struct fsl_sata_channel *ch, union ccb *ccb)
{
	int t = ccb->ccb_h.target_id;

	if ((ccb->ccb_h.func_code == XPT_ATA_IO) &&
	    (ccb->ataio.cmd.flags & CAM_ATAIO_FPDMA)) {
		/* Tagged command while we have no supported tag free. */
		if (((~ch->oslots) & (0xffff >> (16 - ch->curr[t].tags))) == 0)
			return (1);
		/* Tagged command while untagged are active. */
		if (ch->numrslotspd[t] != 0 && ch->numtslotspd[t] == 0)
			return (1);
	} else {
		/* Untagged command while tagged are active. */
		if (ch->numrslotspd[t] != 0 && ch->numtslotspd[t] != 0)
			return (1);
	}
	if ((ccb->ccb_h.func_code == XPT_ATA_IO) &&
	    (ccb->ataio.cmd.flags & (CAM_ATAIO_CONTROL | CAM_ATAIO_NEEDRESULT))) {
		/* Atomic command while anything active. */
		if (ch->numrslots != 0)
			return (1);
	}
	/* We have some atomic command running. */
	if (ch->aslots != 0)
		return (1);
	return (0);
}