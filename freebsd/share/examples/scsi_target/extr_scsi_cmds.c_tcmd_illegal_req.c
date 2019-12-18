#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct ccb_scsiio {int dummy; } ;
struct TYPE_2__ {scalar_t__ targ_descr; } ;
struct ccb_accept_tio {int /*<<< orphan*/  init_id; TYPE_1__ ccb_h; } ;
struct atio_descr {int /*<<< orphan*/  cdb; } ;

/* Variables and functions */
 int /*<<< orphan*/  SSD_KEY_ILLEGAL_REQUEST ; 
 int /*<<< orphan*/  cdb_debug (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ debug ; 
 int /*<<< orphan*/  tcmd_sense (int /*<<< orphan*/ ,struct ccb_scsiio*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
tcmd_illegal_req(struct ccb_accept_tio *atio, struct ccb_scsiio *ctio)
{
	if (debug) {
		struct atio_descr *a_descr;

		a_descr = (struct atio_descr *)atio->ccb_h.targ_descr;
		cdb_debug(a_descr->cdb, "Sending ill req to %u: ", atio->init_id);
	}
	
	tcmd_sense(atio->init_id, ctio, SSD_KEY_ILLEGAL_REQUEST,
		   /*asc*/0x24, /*ascq*/0);
	return (0);
}