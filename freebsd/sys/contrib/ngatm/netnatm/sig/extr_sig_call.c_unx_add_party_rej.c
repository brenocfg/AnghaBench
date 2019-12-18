#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct uni_msg {int dummy; } ;
struct TYPE_8__ {int /*<<< orphan*/  act; int /*<<< orphan*/  cref; } ;
struct TYPE_10__ {int /*<<< orphan*/  flag; int /*<<< orphan*/  epref; } ;
struct uni_add_party_rej {TYPE_3__ epref; int /*<<< orphan*/  cause; } ;
struct TYPE_9__ {TYPE_1__ hdr; struct uni_add_party_rej add_party_rej; } ;
struct uni_all {TYPE_2__ u; } ;
struct party {int /*<<< orphan*/  state; } ;
struct call {int /*<<< orphan*/  uni; int /*<<< orphan*/  cstate; } ;

/* Variables and functions */
 scalar_t__ IE_ISGOOD (TYPE_3__) ; 
 int /*<<< orphan*/  IE_ISPRESENT (TYPE_3__) ; 
 int /*<<< orphan*/  SIGP_ADD_PARTY_REJ ; 
 int /*<<< orphan*/  UNI_CAUSE_MSG_INCOMP ; 
 int /*<<< orphan*/  UNI_FREE (struct uni_all*) ; 
 int /*<<< orphan*/  UNI_IE_EPREF ; 
#define  VFY_CLR 134 
#define  VFY_I 133 
#define  VFY_OK 132 
#define  VFY_RAI 131 
#define  VFY_RAIM 130 
#define  VFY_RAP 129 
#define  VFY_RAPU 128 
 int /*<<< orphan*/  clear_callD (struct call*) ; 
 int /*<<< orphan*/  default_act_epref (int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  handle_bad_drop_cause (struct call*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  map_callstate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uni_bad_message (struct call*,struct uni_all*,int /*<<< orphan*/ ,TYPE_3__*,int) ; 
 int /*<<< orphan*/  uni_enq_party (struct party*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct uni_msg*,struct uni_all*) ; 
 struct party* uni_find_partyx (struct call*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uni_mandate_ie (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uni_msg_destroy (struct uni_msg*) ; 
 int /*<<< orphan*/  uni_respond_status_verify (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ ) ; 
 int uni_verify (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uni_vfy_collect_ies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uni_vfy_remove_unknown (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
unx_add_party_rej(struct call *c, struct uni_msg *m, struct uni_all *u,
    int legal)
{
	struct uni_add_party_rej *ar = &u->u.add_party_rej;
	struct party *p;

	if (IE_ISGOOD(ar->epref)) {
		p = uni_find_partyx(c, ar->epref.epref, ar->epref.flag);
		if (p == NULL)
			goto ignore;

		if (legal) {
			handle_bad_drop_cause(c, &ar->cause, 0);
			uni_vfy_remove_unknown(c->uni);
			switch (uni_verify(c->uni, u->u.hdr.act)) {

			  case VFY_CLR:
				goto clear;

			  case VFY_RAIM:
			  case VFY_RAI:
				uni_respond_status_verify(c->uni,
				    &u->u.hdr.cref, map_callstate(c->cstate),
				    &ar->epref, p->state);
			  case VFY_I:
				goto ignore;

			  case VFY_RAPU:
				uni_vfy_collect_ies(c->uni);
				break;

			  case VFY_RAP:
				uni_respond_status_verify(c->uni,
				    &u->u.hdr.cref, map_callstate(c->cstate),
				    &ar->epref, p->state);
			  case VFY_OK:
				break;
			}
			uni_enq_party(p, SIGP_ADD_PARTY_REJ, 0, m, u);
			return;
		}
		uni_bad_message(c, u, UNI_CAUSE_MSG_INCOMP,
		    &ar->epref, -1);
		return;
	}

	/* Q.2971: 9.5.3.2.1 last paragraph
	 *         9.5.3.2.2 second to last paragraph
	 * Make the action indicator default.
	 */
	default_act_epref(c->uni, &ar->epref);
	if (!IE_ISPRESENT(ar->epref))
		uni_mandate_ie(c->uni, UNI_IE_EPREF);
	(void)uni_verify(c->uni, u->u.hdr.act);

  clear:
	uni_vfy_collect_ies(c->uni);
	clear_callD(c);

  ignore:
	uni_msg_destroy(m);
	UNI_FREE(u);
}