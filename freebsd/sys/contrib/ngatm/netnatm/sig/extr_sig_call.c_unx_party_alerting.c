#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_8__ ;
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
struct uni_msg {int dummy; } ;
struct TYPE_15__ {int /*<<< orphan*/  act; } ;
struct TYPE_20__ {scalar_t__ flag; int /*<<< orphan*/  epref; TYPE_1__ h; } ;
struct TYPE_17__ {TYPE_8__ epref; } ;
struct TYPE_16__ {int /*<<< orphan*/  cref; int /*<<< orphan*/  act; } ;
struct TYPE_18__ {TYPE_3__ party_alerting; TYPE_2__ hdr; } ;
struct uni_all {TYPE_4__ u; } ;
struct party {int /*<<< orphan*/  state; } ;
struct call {int /*<<< orphan*/  cstate; TYPE_5__* uni; } ;
struct TYPE_19__ {int /*<<< orphan*/  cx; } ;

/* Variables and functions */
 scalar_t__ IE_ISGOOD (TYPE_8__) ; 
 int /*<<< orphan*/  IE_SETERROR (TYPE_8__) ; 
 int /*<<< orphan*/  SIGP_PARTY_ALERTING ; 
 int /*<<< orphan*/  UNI_CAUSE_ENDP_INV ; 
 int /*<<< orphan*/  UNI_CAUSE_MSG_INCOMP ; 
 int /*<<< orphan*/  UNI_EPSTATE_ALERT_RCVD ; 
 int /*<<< orphan*/  UNI_EPSTATE_NULL ; 
 int /*<<< orphan*/  UNI_FREE (struct uni_all*) ; 
 int /*<<< orphan*/  UNI_IERR_BAD ; 
 int /*<<< orphan*/  UNI_IE_EPREF ; 
 int /*<<< orphan*/  UNI_SAVE_IERR (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
#define  VFY_CLR 134 
#define  VFY_I 133 
#define  VFY_OK 132 
#define  VFY_RAI 131 
#define  VFY_RAIM 130 
#define  VFY_RAP 129 
#define  VFY_RAPU 128 
 int /*<<< orphan*/  clear_callD (struct call*) ; 
 int /*<<< orphan*/  map_callstate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  respond_drop_party_ack (struct call*,TYPE_8__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uni_bad_message (struct call*,struct uni_all*,int /*<<< orphan*/ ,TYPE_8__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uni_enq_party (struct party*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct uni_msg*,struct uni_all*) ; 
 struct party* uni_find_partyx (struct call*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  uni_mandate_epref (TYPE_5__*,TYPE_8__*) ; 
 int /*<<< orphan*/  uni_msg_destroy (struct uni_msg*) ; 
 int /*<<< orphan*/  uni_respond_status_verify (TYPE_5__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_8__*,int /*<<< orphan*/ ) ; 
 int uni_verify (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uni_vfy_collect_ies (TYPE_5__*) ; 

__attribute__((used)) static void
unx_party_alerting(struct call *c, struct uni_msg *m, struct uni_all *u,
    int legal)
{
	struct party *p = NULL;

	if (IE_ISGOOD(u->u.party_alerting.epref)) {
		if (u->u.party_alerting.epref.flag == 0) {
			IE_SETERROR(u->u.party_alerting.epref);
			(void)UNI_SAVE_IERR(&c->uni->cx, UNI_IE_EPREF,
			    u->u.party_alerting.epref.h.act, UNI_IERR_BAD);
		} else {
	    		p = uni_find_partyx(c, u->u.party_alerting.epref.epref, 1);
			if (p == NULL) {
				respond_drop_party_ack(c,
				    &u->u.party_alerting.epref,
				    UNI_CAUSE_ENDP_INV);
				goto ignore;
			}
		}
	}
	uni_mandate_epref(c->uni, &u->u.party_alerting.epref);

	switch (uni_verify(c->uni, u->u.hdr.act)) {

	  case VFY_CLR:
		uni_vfy_collect_ies(c->uni);
		clear_callD(c);
		goto ignore;

	  case VFY_RAIM:
	  case VFY_RAI:
	  report:
		uni_respond_status_verify(c->uni, &u->u.hdr.cref,
		    map_callstate(c->cstate), &u->u.party_alerting.epref,
		    p ? p->state : UNI_EPSTATE_NULL);
	  case VFY_I:
		goto ignore;

	  case VFY_RAP:
	  case VFY_RAPU:
		uni_respond_status_verify(c->uni, &u->u.hdr.cref,
		    map_callstate(c->cstate), &u->u.party_alerting.epref,
		    p ? UNI_EPSTATE_ALERT_RCVD : UNI_EPSTATE_NULL);
		if (!IE_ISGOOD(u->u.party_alerting.epref))
			/* See below */
			goto ignore;
		break;

	  case VFY_OK:
		if (!IE_ISGOOD(u->u.party_alerting.epref))
			/* The rules require us the message to be ignored
			 * (9.5.3.2.2e) and to report status.
			 */
			goto report;
		break;
	}
	if (legal) {
		/* p is != NULL here */
		uni_enq_party(p, SIGP_PARTY_ALERTING, 0, m, u);
		return;
	}
	if (p == NULL)
		/* Q.2971 9.5.3.2.3a) */
		respond_drop_party_ack(c, &u->u.party_alerting.epref,
		    UNI_CAUSE_ENDP_INV);
	else
		uni_bad_message(c, u, UNI_CAUSE_MSG_INCOMP,
		    &u->u.party_alerting.epref, p->state);

  ignore:
	uni_msg_destroy(m);
	UNI_FREE(u);
}