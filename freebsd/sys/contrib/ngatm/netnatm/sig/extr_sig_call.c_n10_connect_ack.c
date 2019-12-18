#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct uni_msg {int dummy; } ;
struct TYPE_7__ {int /*<<< orphan*/  cref; int /*<<< orphan*/  act; } ;
struct TYPE_6__ {TYPE_2__ hdr; } ;
struct uni_all {TYPE_1__ u; } ;
struct call {int /*<<< orphan*/  cstate; TYPE_3__* uni; } ;
struct TYPE_8__ {int /*<<< orphan*/  cx; } ;

/* Variables and functions */
 int /*<<< orphan*/  UNI_FREE (struct uni_all*) ; 
#define  VFY_CLR 134 
#define  VFY_I 133 
#define  VFY_OK 132 
#define  VFY_RAI 131 
#define  VFY_RAIM 130 
#define  VFY_RAP 129 
#define  VFY_RAPU 128 
 int /*<<< orphan*/  clear_callD (struct call*) ; 
 int /*<<< orphan*/  map_callstate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uni_decode_body (struct uni_msg*,struct uni_all*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uni_msg_destroy (struct uni_msg*) ; 
 int /*<<< orphan*/  uni_respond_status_verify (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int uni_verify (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uni_vfy_collect_ies (TYPE_3__*) ; 

__attribute__((used)) static void
n10_connect_ack(struct call *c, struct uni_msg *m, struct uni_all *u)
{
	/*
	 * Analyze message
	 */
	(void)uni_decode_body(m, u, &c->uni->cx);

	switch (uni_verify(c->uni, u->u.hdr.act)) {

	  case VFY_CLR:
		uni_vfy_collect_ies(c->uni);
		clear_callD(c);
		/* FALLTHRU */
	  case VFY_I:
		uni_msg_destroy(m);
		UNI_FREE(u);
	  	return;

	  case VFY_RAIM:
	  case VFY_RAI:
	  case VFY_RAP:
	  case VFY_RAPU:
		uni_respond_status_verify(c->uni, &u->u.hdr.cref,
		    map_callstate(c->cstate), NULL, 0);
		/* FALLTHRU */
	  case VFY_OK:
		uni_msg_destroy(m);
		UNI_FREE(u);
	  	return;
	}
}