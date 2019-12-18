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
struct twa_softc {int dummy; } ;
struct TYPE_2__ {scalar_t__ is_io; int /*<<< orphan*/ * cl_req_ctxt; int /*<<< orphan*/ * osl_req_ctxt; } ;
struct tw_osli_req_context {int /*<<< orphan*/  req_pkt; int /*<<< orphan*/ * orig_req; scalar_t__ error_code; scalar_t__ flags; int /*<<< orphan*/  state; scalar_t__ real_length; int /*<<< orphan*/ * real_data; scalar_t__ deadline; scalar_t__ length; int /*<<< orphan*/ * data; TYPE_1__ req_handle; } ;
struct tw_cl_req_packet {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TW_OSLI_FREE_Q ; 
 int /*<<< orphan*/  TW_OSLI_REQ_STATE_INIT ; 
 int /*<<< orphan*/  bzero (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  tw_osli_dbg_dprintf (int,struct twa_softc*,char*) ; 
 struct tw_osli_req_context* tw_osli_req_q_remove_head (struct twa_softc*,int /*<<< orphan*/ ) ; 

struct tw_osli_req_context *
tw_osli_get_request(struct twa_softc *sc)
{
	struct tw_osli_req_context	*req;

	tw_osli_dbg_dprintf(4, sc, "entered");

	/* Get a free request packet. */
	req = tw_osli_req_q_remove_head(sc, TW_OSLI_FREE_Q);

	/* Initialize some fields to their defaults. */
	if (req) {
		req->req_handle.osl_req_ctxt = NULL;
		req->req_handle.cl_req_ctxt = NULL;
		req->req_handle.is_io = 0;
		req->data = NULL;
		req->length = 0;
		req->deadline = 0;
		req->real_data = NULL;
		req->real_length = 0;
		req->state = TW_OSLI_REQ_STATE_INIT;/* req being initialized */
		req->flags = 0;
		req->error_code = 0;
		req->orig_req = NULL;

		bzero(&(req->req_pkt), sizeof(struct tw_cl_req_packet));

	}
	return(req);
}