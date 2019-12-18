#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_7__ {scalar_t__ cdb_bytes; scalar_t__ cdb_ptr; } ;
struct ccb_hdr {int flags; } ;
struct ccb_scsiio {int cdb_len; TYPE_1__ cdb_io; struct ccb_hdr ccb_h; } ;
typedef  int /*<<< orphan*/  hcb_p ;
typedef  TYPE_4__* ccb_p ;
struct TYPE_8__ {void* size; void* addr; } ;
struct TYPE_9__ {TYPE_2__ cmd; } ;
struct TYPE_10__ {TYPE_3__ phys; int /*<<< orphan*/  cdb_buf; int /*<<< orphan*/  cam_ccb; } ;

/* Variables and functions */
 int CAM_CDB_PHYS ; 
 int CAM_CDB_POINTER ; 
 int /*<<< orphan*/  CAM_REQ_INVALID ; 
 int CCB_BA (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  SYM_LOCK_ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcopy (scalar_t__,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * cdb_buf ; 
 void* cpu_to_scr (int) ; 
 int /*<<< orphan*/  sym_set_cam_status (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sym_setup_cdb(hcb_p np, struct ccb_scsiio *csio, ccb_p cp)
{
	struct ccb_hdr *ccb_h;
	u32	cmd_ba;
	int	cmd_len;

	SYM_LOCK_ASSERT(MA_OWNED);

	ccb_h = &csio->ccb_h;

	/*
	 *  CDB is 16 bytes max.
	 */
	if (csio->cdb_len > sizeof(cp->cdb_buf)) {
		sym_set_cam_status(cp->cam_ccb, CAM_REQ_INVALID);
		return -1;
	}
	cmd_len = csio->cdb_len;

	if (ccb_h->flags & CAM_CDB_POINTER) {
		/* CDB is a pointer */
		if (!(ccb_h->flags & CAM_CDB_PHYS)) {
			/* CDB pointer is virtual */
			bcopy(csio->cdb_io.cdb_ptr, cp->cdb_buf, cmd_len);
			cmd_ba = CCB_BA (cp, cdb_buf[0]);
		} else {
			/* CDB pointer is physical */
#if 0
			cmd_ba = ((u32)csio->cdb_io.cdb_ptr) & 0xffffffff;
#else
			sym_set_cam_status(cp->cam_ccb, CAM_REQ_INVALID);
			return -1;
#endif
		}
	} else {
		/* CDB is in the CAM ccb (buffer) */
		bcopy(csio->cdb_io.cdb_bytes, cp->cdb_buf, cmd_len);
		cmd_ba = CCB_BA (cp, cdb_buf[0]);
	}

	cp->phys.cmd.addr	= cpu_to_scr(cmd_ba);
	cp->phys.cmd.size	= cpu_to_scr(cmd_len);

	return 0;
}