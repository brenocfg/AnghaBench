#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int func_code; } ;
struct TYPE_10__ {scalar_t__ targ_descr; } ;
struct ccb_scsiio {TYPE_3__ ccb_h; } ;
struct TYPE_9__ {int /*<<< orphan*/  cdb_ptr; int /*<<< orphan*/  cdb_bytes; } ;
struct TYPE_8__ {int flags; scalar_t__ targ_descr; } ;
struct ccb_accept_tio {TYPE_2__ cdb_io; TYPE_1__ ccb_h; } ;
union ccb {TYPE_5__ ccb_h; struct ccb_scsiio ctio; struct ccb_accept_tio atio; } ;
struct ctio_descr {int /*<<< orphan*/  atio; int /*<<< orphan*/  event; } ;
struct atio_descr {int flags; int /*<<< orphan*/  cdb; int /*<<< orphan*/  cmplt_io; } ;
typedef  int /*<<< orphan*/  ccb_array ;
struct TYPE_11__ {int /*<<< orphan*/  tqe; } ;

/* Variables and functions */
 int CAM_CDB_POINTER ; 
 int CAM_DIS_DISCONNECT ; 
 int CAM_TAG_ACTION_VALID ; 
 int /*<<< orphan*/  CTIO_DONE ; 
 int MAX_INITIATORS ; 
 int /*<<< orphan*/  TAILQ_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_INSERT_HEAD (int /*<<< orphan*/ *,TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,TYPE_5__*,int /*<<< orphan*/ ) ; 
#define  XPT_ACCEPT_TARGET_IO 130 
#define  XPT_CONT_TARGET_IO 129 
#define  XPT_IMMEDIATE_NOTIFY 128 
 int /*<<< orphan*/  bzero (struct atio_descr*,int) ; 
 int /*<<< orphan*/  pending_queue ; 
 TYPE_4__ periph_links ; 
 int /*<<< orphan*/  queue_io (struct ccb_scsiio*) ; 
 int read (int /*<<< orphan*/ ,union ccb**,int) ; 
 int run_queue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  targ_fd ; 
 int /*<<< orphan*/  warn (char*) ; 
 int /*<<< orphan*/  warnx (char*,...) ; 
 int /*<<< orphan*/  work_queue ; 

__attribute__((used)) static void
handle_read()
{
	union ccb *ccb_array[MAX_INITIATORS], *ccb;
	int ccb_count, i, oo;

	ccb_count = read(targ_fd, ccb_array, sizeof(ccb_array));
	if (ccb_count <= 0) {
		warn("read ccb ptrs");
		return;
	}
	ccb_count /= sizeof(union ccb *);
	if (ccb_count < 1) {
		warnx("truncated read ccb ptr?");
		return;
	}

	for (i = 0; i < ccb_count; i++) {
		ccb = ccb_array[i];
		TAILQ_REMOVE(&pending_queue, &ccb->ccb_h, periph_links.tqe);

		switch (ccb->ccb_h.func_code) {
		case XPT_ACCEPT_TARGET_IO:
		{
			struct ccb_accept_tio *atio;
			struct atio_descr *a_descr;

			/* Initialize ATIO descr for this transaction */
			atio = &ccb->atio;
			a_descr = (struct atio_descr *)atio->ccb_h.targ_descr;
			bzero(a_descr, sizeof(*a_descr));
			TAILQ_INIT(&a_descr->cmplt_io);
			a_descr->flags = atio->ccb_h.flags &
				(CAM_DIS_DISCONNECT | CAM_TAG_ACTION_VALID);
			/* XXX add a_descr->priority */
			if ((atio->ccb_h.flags & CAM_CDB_POINTER) == 0)
				a_descr->cdb = atio->cdb_io.cdb_bytes;
			else
				a_descr->cdb = atio->cdb_io.cdb_ptr;

			/* ATIOs are processed in FIFO order */
			TAILQ_INSERT_TAIL(&work_queue, &ccb->ccb_h,
					  periph_links.tqe);
			break;
		}
		case XPT_CONT_TARGET_IO:
		{
			struct ccb_scsiio *ctio;
			struct ctio_descr *c_descr;

			ctio = &ccb->ctio;
			c_descr = (struct ctio_descr *)ctio->ccb_h.targ_descr;
			c_descr->event = CTIO_DONE;
			/* Queue on the appropriate ATIO */
			queue_io(ctio);
			/* Process any queued completions. */
			oo += run_queue(c_descr->atio);
			break;
		}
		case XPT_IMMEDIATE_NOTIFY:
			/* INOTs are handled with priority */
			TAILQ_INSERT_HEAD(&work_queue, &ccb->ccb_h,
					  periph_links.tqe);
			break;
		default:
			warnx("Unhandled ccb type %#x in handle_read",
			      ccb->ccb_h.func_code);
			break;
		}
	}
}