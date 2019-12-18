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
struct TYPE_6__ {scalar_t__ func_code; size_t target_id; } ;
union ccb {TYPE_4__ ataio; TYPE_2__ ccb_h; } ;
struct siis_channel {int oslots; scalar_t__ numrslots; scalar_t__ aslots; TYPE_1__* curr; int /*<<< orphan*/  mtx; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_5__ {int tags; } ;

/* Variables and functions */
 int CAM_ATAIO_CONTROL ; 
 int CAM_ATAIO_FPDMA ; 
 int CAM_ATAIO_NEEDRESULT ; 
 int /*<<< orphan*/  MA_OWNED ; 
 scalar_t__ XPT_ATA_IO ; 
 struct siis_channel* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
siis_check_collision(device_t dev, union ccb *ccb)
{
	struct siis_channel *ch = device_get_softc(dev);

	mtx_assert(&ch->mtx, MA_OWNED);
	if ((ccb->ccb_h.func_code == XPT_ATA_IO) &&
	    (ccb->ataio.cmd.flags & CAM_ATAIO_FPDMA)) {
		/* Tagged command while we have no supported tag free. */
		if (((~ch->oslots) & (0x7fffffff >> (31 -
		    ch->curr[ccb->ccb_h.target_id].tags))) == 0)
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