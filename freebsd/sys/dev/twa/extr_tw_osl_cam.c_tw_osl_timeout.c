#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct ccb_hdr {int timeout; } ;
union ccb {struct ccb_hdr ccb_h; } ;
struct tw_osli_req_context {scalar_t__ deadline; scalar_t__ orig_req; } ;
struct tw_cl_req_handle {struct tw_osli_req_context* osl_req_ctxt; } ;
typedef  int /*<<< orphan*/  TW_VOID ;

/* Variables and functions */
 scalar_t__ tw_osl_get_local_time () ; 

TW_VOID
tw_osl_timeout(struct tw_cl_req_handle *req_handle)
{
	struct tw_osli_req_context	*req = req_handle->osl_req_ctxt;
	union ccb			*ccb = (union ccb *)(req->orig_req);
	struct ccb_hdr			*ccb_h = &(ccb->ccb_h);

	req->deadline = tw_osl_get_local_time() + (ccb_h->timeout / 1000);
}