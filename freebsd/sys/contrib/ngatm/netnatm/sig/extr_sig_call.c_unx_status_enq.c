#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_8__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_int ;
struct uni_msg {int dummy; } ;
struct TYPE_12__ {int /*<<< orphan*/  cause; int /*<<< orphan*/  callstate; int /*<<< orphan*/  epstate; int /*<<< orphan*/  epref; } ;
struct TYPE_15__ {int /*<<< orphan*/  flag; int /*<<< orphan*/  epref; } ;
struct TYPE_11__ {TYPE_8__ epref; } ;
struct TYPE_10__ {int /*<<< orphan*/  act; } ;
struct TYPE_13__ {TYPE_3__ status; TYPE_2__ status_enq; TYPE_1__ hdr; } ;
struct uni_all {TYPE_4__ u; } ;
struct party {int /*<<< orphan*/  state; } ;
struct call {scalar_t__ type; TYPE_5__* uni; int /*<<< orphan*/  cstate; int /*<<< orphan*/  mine; int /*<<< orphan*/  cref; } ;
struct TYPE_14__ {int /*<<< orphan*/  cx; } ;

/* Variables and functions */
 scalar_t__ CALL_LEAF ; 
 scalar_t__ CALL_ROOT ; 
 scalar_t__ IE_ISGOOD (TYPE_8__) ; 
 int /*<<< orphan*/  MK_IE_CALLSTATE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MK_IE_CAUSE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MK_IE_EPREF (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  MK_IE_EPSTATE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MK_MSG_ORIG (struct uni_all*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  UNI_CAUSE_LOC_USER ; 
 int /*<<< orphan*/  UNI_CAUSE_STATUS ; 
 int /*<<< orphan*/  UNI_EPSTATE_NULL ; 
 int /*<<< orphan*/  UNI_FREE (struct uni_all*) ; 
 int /*<<< orphan*/  UNI_STATUS ; 
#define  VFY_CLR 134 
#define  VFY_I 133 
#define  VFY_OK 132 
#define  VFY_RAI 131 
#define  VFY_RAIM 130 
#define  VFY_RAP 129 
#define  VFY_RAPU 128 
 int /*<<< orphan*/  clear_callD (struct call*) ; 
 int /*<<< orphan*/  map_callstate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct uni_all*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  uni_decode_body (struct uni_msg*,struct uni_all*,int /*<<< orphan*/ *) ; 
 struct party* uni_find_party (struct call*,TYPE_8__*) ; 
 int /*<<< orphan*/  uni_msg_destroy (struct uni_msg*) ; 
 int /*<<< orphan*/  uni_send_output (struct uni_all*,TYPE_5__*) ; 
 int uni_verify (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uni_vfy_collect_ies (TYPE_5__*) ; 

__attribute__((used)) static void
unx_status_enq(struct call *c, struct uni_msg *m, struct uni_all *u)
{
	struct party *p = NULL;
	u_int epref, flag;

	/*
	 * Analyze message
	 */
	(void)uni_decode_body(m, u, &c->uni->cx);

	switch (uni_verify(c->uni, u->u.hdr.act)) {

	  case VFY_CLR:
		uni_vfy_collect_ies(c->uni);
		clear_callD(c);
		uni_msg_destroy(m);
		UNI_FREE(u);
	  	return;

	  case VFY_RAIM:
	  case VFY_RAI:
	  case VFY_RAP:
	  case VFY_RAPU:
	  case VFY_I:
	  case VFY_OK:
	  	break;
	}

	uni_msg_destroy(m);

	if ((c->type == CALL_ROOT || c->type == CALL_LEAF) &&
	    IE_ISGOOD(u->u.status_enq.epref)) {
		p = uni_find_party(c, &u->u.status_enq.epref);

		epref = u->u.status_enq.epref.epref;
		flag = u->u.status_enq.epref.flag;
		memset(u, 0, sizeof(*u));
		MK_IE_EPREF(u->u.status.epref, epref, !flag);

		if (p != NULL)
			MK_IE_EPSTATE(u->u.status.epstate, p->state);
		else
			MK_IE_EPSTATE(u->u.status.epstate, UNI_EPSTATE_NULL);
	} else
		memset(u, 0, sizeof(*u));


	MK_MSG_ORIG(u, UNI_STATUS, c->cref, !c->mine);
	MK_IE_CALLSTATE(u->u.status.callstate, map_callstate(c->cstate));
	MK_IE_CAUSE(u->u.status.cause, UNI_CAUSE_LOC_USER, UNI_CAUSE_STATUS);
	(void)uni_send_output(u, c->uni);
	UNI_FREE(u);
}