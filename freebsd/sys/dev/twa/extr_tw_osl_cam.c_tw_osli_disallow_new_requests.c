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
struct TYPE_2__ {int /*<<< orphan*/  status; } ;
union ccb {TYPE_1__ ccb_h; } ;
struct twa_softc {int /*<<< orphan*/  sim; } ;
struct tw_osli_req_context {scalar_t__ orig_req; } ;
struct tw_cl_req_handle {struct tw_osli_req_context* osl_req_ctxt; scalar_t__ is_io; } ;
typedef  int /*<<< orphan*/  TW_VOID ;

/* Variables and functions */
 int /*<<< orphan*/  CAM_RELEASE_SIMQ ; 
 int /*<<< orphan*/  xpt_freeze_simq (int /*<<< orphan*/ ,int) ; 

TW_VOID
tw_osli_disallow_new_requests(struct twa_softc *sc,
	struct tw_cl_req_handle *req_handle)
{
	/* Only freeze/release the simq for IOs */
	if (req_handle->is_io) {
		struct tw_osli_req_context	*req = req_handle->osl_req_ctxt;
		union ccb			*ccb = (union ccb *)(req->orig_req);

		xpt_freeze_simq(sc->sim, 1);
		ccb->ccb_h.status |= CAM_RELEASE_SIMQ;
	}
}