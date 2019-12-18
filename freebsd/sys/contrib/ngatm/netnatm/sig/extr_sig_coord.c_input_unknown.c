#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_int ;
struct uni_msg {int dummy; } ;
struct TYPE_13__ {int /*<<< orphan*/ * cause; } ;
struct TYPE_15__ {int /*<<< orphan*/  cref; int /*<<< orphan*/  flag; } ;
struct TYPE_12__ {TYPE_6__ cref; } ;
struct TYPE_16__ {int /*<<< orphan*/  flag; int /*<<< orphan*/  epref; int /*<<< orphan*/  state; } ;
struct TYPE_11__ {int /*<<< orphan*/  epstate; TYPE_7__ epref; int /*<<< orphan*/  cause; TYPE_7__ callstate; } ;
struct TYPE_10__ {TYPE_7__ epref; } ;
struct TYPE_14__ {TYPE_4__ release_compl; TYPE_3__ hdr; TYPE_2__ status; TYPE_1__ status_enq; } ;
struct uni_all {int mtype; TYPE_5__ u; } ;
struct uni {int /*<<< orphan*/  cx; } ;
struct call {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADD_CAUSE_MTYPE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  IE_ISGOOD (TYPE_7__) ; 
 int /*<<< orphan*/  MK_IE_CALLSTATE (TYPE_7__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MK_IE_CAUSE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MK_IE_EPREF (TYPE_7__,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  MK_IE_EPSTATE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MK_MSG_RESP (struct uni_all*,int const,TYPE_6__*) ; 
 int /*<<< orphan*/  SIGC_COBISETUP ; 
 int /*<<< orphan*/  SIGC_SETUP ; 
 struct uni_all* UNI_ALLOC () ; 
 int /*<<< orphan*/  UNI_CALLSTATE_U0 ; 
 int /*<<< orphan*/  UNI_CAUSE_CREF_INV ; 
 int /*<<< orphan*/  UNI_CAUSE_LOC_USER ; 
 int /*<<< orphan*/  UNI_CAUSE_MSG_INCOMP ; 
 int /*<<< orphan*/  UNI_CAUSE_STATUS ; 
#define  UNI_COBISETUP 132 
 int /*<<< orphan*/  UNI_CODING_ITU ; 
 scalar_t__ UNI_DIAG_MTYPE ; 
 int /*<<< orphan*/  UNI_EPSTATE_NULL ; 
 int /*<<< orphan*/  UNI_FAC_COORD ; 
 int /*<<< orphan*/  UNI_FREE (struct uni_all*) ; 
#define  UNI_RELEASE_COMPL 131 
#define  UNI_SETUP 130 
#define  UNI_STATUS 129 
#define  UNI_STATUS_ENQ 128 
 int /*<<< orphan*/  VERBOSE (struct uni*,int /*<<< orphan*/ ,int,char*,int) ; 
 struct call* uni_create_call (struct uni*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uni_decode_body (struct uni_msg*,struct uni_all*,int /*<<< orphan*/ *) ; 
 scalar_t__ uni_diag (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uni_enq_call (struct call*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct uni_msg*,struct uni_all*) ; 
 int /*<<< orphan*/  uni_msg_destroy (struct uni_msg*) ; 
 int /*<<< orphan*/  uni_send_output (struct uni_all*,struct uni*) ; 

__attribute__((used)) static void
input_unknown(struct uni *uni, struct uni_msg *m, struct uni_all *u)
{
	struct uni_all *resp;
	struct call *c;
	u_int cause = UNI_CAUSE_CREF_INV;

	VERBOSE(uni, UNI_FAC_COORD, 2, "UNKNOWN MTYPE = %x", u->mtype);

	switch (u->mtype) {

	  default:
		/*
		 * This message type is entirly unknown
		 *
		 * 5.6.4 and 5.7.1 are only when the call is not in the
		 * NULL state. This means, 5.6.3.2a takes over.
		 */
		break;

	  case UNI_SETUP:
		if (u->u.hdr.cref.flag)
			/*
			 * 5.6.3.2c
			 */
			goto drop;
		if ((c = uni_create_call(uni, u->u.hdr.cref.cref, 0, 0)) != NULL) {
			uni_enq_call(c, SIGC_SETUP, 0, m, u);
			return;
		}
		goto drop;

	  case UNI_RELEASE_COMPL:
		/*
		 * 5.6.3.2c
		 */
		goto drop;

	  case UNI_STATUS:
		/*
		 * 5.6.12
		 *
		 * The SDLs don't use the verify procedure and don't
		 * handle the case of an invalid callstate - we
		 * ignore the message, if the callstate is not good.
		 */
		(void)uni_decode_body(m, u, &uni->cx);
		if (!IE_ISGOOD(u->u.status.callstate))
			goto drop;
		if (u->u.status.callstate.state == UNI_CALLSTATE_U0)
			goto drop;
		cause = UNI_CAUSE_MSG_INCOMP;
		break;

	  case UNI_STATUS_ENQ:
		if ((resp = UNI_ALLOC()) == NULL)
			goto drop;

		(void)uni_decode_body(m, u, &uni->cx);
		MK_MSG_RESP(resp, UNI_STATUS, &u->u.hdr.cref);
		MK_IE_CALLSTATE(resp->u.status.callstate, UNI_CALLSTATE_U0);
		MK_IE_CAUSE(resp->u.status.cause, UNI_CAUSE_LOC_USER,
		    UNI_CAUSE_STATUS);

		if (IE_ISGOOD(u->u.status_enq.epref)) {
			/* reflect epref as required by L3MU_PO */
			resp->u.status.epref = u->u.status_enq.epref;
			MK_IE_EPREF(resp->u.status.epref,
			    u->u.status_enq.epref.epref,
			    !u->u.status_enq.epref.flag);
			MK_IE_EPSTATE(resp->u.status.epstate, UNI_EPSTATE_NULL);
		}

		(void)uni_send_output(resp, uni);

		UNI_FREE(resp);
		goto drop;

	  case UNI_COBISETUP:
		if (u->u.hdr.cref.flag)
			/*
			 * 5.6.3.2c (probably)
			 */
			goto drop;
		if ((c = uni_create_call(uni, u->u.hdr.cref.cref, 0, 0)) != NULL) {
			uni_enq_call(c, SIGC_COBISETUP, 0, m, u);
			return;
		}
		goto drop;
	}

	/*
	 * 5.6.3.2a)
	 *
	 * Respond with a RELEASE COMPLETE
	 */
	if ((resp = UNI_ALLOC()) == NULL)
		goto drop;

	MK_MSG_RESP(resp, UNI_RELEASE_COMPL, &u->u.hdr.cref);
	MK_IE_CAUSE(resp->u.release_compl.cause[0], UNI_CAUSE_LOC_USER, cause);
	if (uni_diag(cause, UNI_CODING_ITU) == UNI_DIAG_MTYPE)
		ADD_CAUSE_MTYPE(resp->u.release_compl.cause[0], u->mtype);

	(void)uni_send_output(resp, uni);

	UNI_FREE(resp);

  drop:
	UNI_FREE(u);
	uni_msg_destroy(m);
}