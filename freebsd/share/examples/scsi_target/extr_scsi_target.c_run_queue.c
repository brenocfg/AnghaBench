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
typedef  union ccb {int dummy; } ccb ;
struct ctio_descr {int event; scalar_t__ offset; } ;
struct TYPE_5__ {scalar_t__ status; scalar_t__ targ_descr; } ;
struct ccb_scsiio {TYPE_2__ ccb_h; } ;
struct ccb_hdr {int flags; } ;
struct TYPE_4__ {scalar_t__ targ_descr; } ;
struct ccb_accept_tio {TYPE_1__ ccb_h; } ;
struct atio_descr {scalar_t__ base_off; scalar_t__ targ_ack; scalar_t__ init_ack; int /*<<< orphan*/  cmplt_io; } ;
struct TYPE_6__ {int /*<<< orphan*/  tqe; } ;

/* Variables and functions */
 int AIO_DONE ; 
 scalar_t__ CAM_REQ_ABORTED ; 
 int CAM_SEND_STATUS ; 
 int CTIO_DONE ; 
 struct ccb_hdr* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct ccb_hdr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_ccb (union ccb*) ; 
 TYPE_3__ periph_links ; 
 int /*<<< orphan*/  send_ccb (union ccb*,int) ; 
 int /*<<< orphan*/  tcmd_handle (struct ccb_accept_tio*,struct ccb_scsiio*,int) ; 
 int /*<<< orphan*/  warnx (char*,struct ccb_hdr*,struct atio_descr*,char*) ; 

__attribute__((used)) static int
run_queue(struct ccb_accept_tio *atio)
{
	struct atio_descr *a_descr;
	struct ccb_hdr *ccb_h;
	int sent_status, event;

	if (atio == NULL)
		return (0);

	a_descr = (struct atio_descr *)atio->ccb_h.targ_descr;

	while ((ccb_h = TAILQ_FIRST(&a_descr->cmplt_io)) != NULL) {
		struct ccb_scsiio *ctio;
		struct ctio_descr *c_descr;

		ctio = (struct ccb_scsiio *)ccb_h;
		c_descr = (struct ctio_descr *)ctio->ccb_h.targ_descr;

		if (ctio->ccb_h.status == CAM_REQ_ABORTED) {
			TAILQ_REMOVE(&a_descr->cmplt_io, ccb_h,
				     periph_links.tqe);
			free_ccb((union ccb *)ctio);
			send_ccb((union ccb *)atio, /*priority*/1);
			continue;
		}

		/* If completed item is in range, call handler */
		if ((c_descr->event == AIO_DONE &&
		    c_descr->offset == a_descr->base_off + a_descr->targ_ack)
		 || (c_descr->event == CTIO_DONE &&
		    c_descr->offset == a_descr->base_off + a_descr->init_ack)) {
			sent_status = (ccb_h->flags & CAM_SEND_STATUS) != 0;
			event = c_descr->event;

			TAILQ_REMOVE(&a_descr->cmplt_io, ccb_h,
				     periph_links.tqe);
			tcmd_handle(atio, ctio, c_descr->event);

			/* If entire transfer complete, send back ATIO */
			if (sent_status != 0 && event == CTIO_DONE)
				send_ccb((union ccb *)atio, /*priority*/1);
		} else {
			/* Gap in offsets so wait until later callback */
			if (/* debug */ 1)
				warnx("IO %p:%p out of order %s",  ccb_h,
				    a_descr, c_descr->event == AIO_DONE?
				    "aio" : "ctio");
			return (1);
		}
	}
	return (0);
}