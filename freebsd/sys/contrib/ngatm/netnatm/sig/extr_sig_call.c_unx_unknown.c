#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct uni_msg {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  epref; } ;
struct TYPE_6__ {scalar_t__ act; } ;
struct TYPE_7__ {TYPE_1__ unknown; TYPE_2__ hdr; } ;
struct uni_all {TYPE_3__ u; int /*<<< orphan*/  mtype; } ;
struct call {TYPE_4__* uni; } ;
struct TYPE_8__ {int /*<<< orphan*/  cx; int /*<<< orphan*/  cause; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADD_CAUSE_MTYPE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MK_IE_CAUSE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UNI_CAUSE_LOC_USER ; 
 int /*<<< orphan*/  UNI_CAUSE_MTYPE_NIMPL ; 
 int /*<<< orphan*/  UNI_FREE (struct uni_all*) ; 
 scalar_t__ UNI_MSGACT_CLEAR ; 
 scalar_t__ UNI_MSGACT_IGNORE ; 
 int /*<<< orphan*/  clear_callD (struct call*) ; 
 int /*<<< orphan*/  uni_bad_message (struct call*,struct uni_all*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  uni_decode_body (struct uni_msg*,struct uni_all*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uni_msg_destroy (struct uni_msg*) ; 

__attribute__((used)) static void
unx_unknown(struct call *c, struct uni_msg *m, struct uni_all *u)
{
	/*
	 * Unrecognized message. Cannot call verify here, because
	 * it doesn't know about unrecognized messages.
	 */
	if (u->u.hdr.act == UNI_MSGACT_CLEAR) {
		MK_IE_CAUSE(c->uni->cause, UNI_CAUSE_LOC_USER,
		    UNI_CAUSE_MTYPE_NIMPL);
		ADD_CAUSE_MTYPE(c->uni->cause, u->mtype);
		clear_callD(c);
	} else if(u->u.hdr.act == UNI_MSGACT_IGNORE) {
		;
	} else {
		(void)uni_decode_body(m, u, &c->uni->cx);
		uni_bad_message(c, u, UNI_CAUSE_MTYPE_NIMPL,
		    &u->u.unknown.epref, -1);
	}
	uni_msg_destroy(m);
	UNI_FREE(u);
}