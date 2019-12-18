#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int ata_flags; } ;
struct TYPE_4__ {int target_id; scalar_t__ target_lun; scalar_t__ func_code; int /*<<< orphan*/  status; } ;
union ccb {TYPE_1__ ataio; TYPE_2__ ccb_h; } ;
struct ata_channel {int flags; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ATA_FLAG_AUX ; 
 int ATA_NO_SLAVE ; 
 int /*<<< orphan*/  CAM_LUN_INVALID ; 
 int /*<<< orphan*/  CAM_TID_INVALID ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 scalar_t__ XPT_ATA_IO ; 
 struct ata_channel* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xpt_done (union ccb*) ; 

__attribute__((used)) static int
ata_check_ids(device_t dev, union ccb *ccb)
{
	struct ata_channel *ch = device_get_softc(dev);

	if (ccb->ccb_h.target_id > ((ch->flags & ATA_NO_SLAVE) ? 0 : 1)) {
		ccb->ccb_h.status = CAM_TID_INVALID;
		xpt_done(ccb);
		return (-1);
	}
	if (ccb->ccb_h.target_lun != 0) {
		ccb->ccb_h.status = CAM_LUN_INVALID;
		xpt_done(ccb);
		return (-1);
	}
	/*
	 * It's a programming error to see AUXILIARY register requests.
	 */
	KASSERT(ccb->ccb_h.func_code != XPT_ATA_IO ||
	    ((ccb->ataio.ata_flags & ATA_FLAG_AUX) == 0),
	    ("AUX register unsupported"));
	return (0);
}