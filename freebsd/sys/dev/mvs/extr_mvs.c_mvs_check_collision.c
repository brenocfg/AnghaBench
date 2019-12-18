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
struct TYPE_5__ {int flags; } ;
struct TYPE_6__ {TYPE_2__ cmd; } ;
struct TYPE_4__ {scalar_t__ func_code; scalar_t__ target_id; } ;
union ccb {TYPE_3__ ataio; TYPE_1__ ccb_h; } ;
struct mvs_channel {scalar_t__ numdslots; scalar_t__ numpslots; scalar_t__ numtslots; scalar_t__ taggedtarget; scalar_t__ numrslots; scalar_t__ aslots; int /*<<< orphan*/  fbs_enabled; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int CAM_ATAIO_CONTROL ; 
 int CAM_ATAIO_DMA ; 
 int CAM_ATAIO_FPDMA ; 
 int CAM_ATAIO_NEEDRESULT ; 
 scalar_t__ XPT_ATA_IO ; 
 struct mvs_channel* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
mvs_check_collision(device_t dev, union ccb *ccb)
{
	struct mvs_channel *ch = device_get_softc(dev);

	if (ccb->ccb_h.func_code == XPT_ATA_IO) {
		/* NCQ DMA */
		if (ccb->ataio.cmd.flags & CAM_ATAIO_FPDMA) {
			/* Can't mix NCQ and non-NCQ DMA commands. */
			if (ch->numdslots != 0)
				return (1);
			/* Can't mix NCQ and PIO commands. */
			if (ch->numpslots != 0)
				return (1);
			/* If we have no FBS */
			if (!ch->fbs_enabled) {
				/* Tagged command while tagged to other target is active. */
				if (ch->numtslots != 0 &&
				    ch->taggedtarget != ccb->ccb_h.target_id)
					return (1);
			}
		/* Non-NCQ DMA */
		} else if (ccb->ataio.cmd.flags & CAM_ATAIO_DMA) {
			/* Can't mix non-NCQ DMA and NCQ commands. */
			if (ch->numtslots != 0)
				return (1);
			/* Can't mix non-NCQ DMA and PIO commands. */
			if (ch->numpslots != 0)
				return (1);
		/* PIO */
		} else {
			/* Can't mix PIO with anything. */
			if (ch->numrslots != 0)
				return (1);
		}
		if (ccb->ataio.cmd.flags & (CAM_ATAIO_CONTROL | CAM_ATAIO_NEEDRESULT)) {
			/* Atomic command while anything active. */
			if (ch->numrslots != 0)
				return (1);
		}
	} else { /* ATAPI */
		/* ATAPI goes without EDMA, so can't mix it with anything. */
		if (ch->numrslots != 0)
			return (1);
	}
	/* We have some atomic command running. */
	if (ch->aslots != 0)
		return (1);
	return (0);
}