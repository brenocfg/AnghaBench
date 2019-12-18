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
struct TYPE_7__ {scalar_t__ cref; } ;
struct TYPE_5__ {TYPE_3__ cref; } ;
struct TYPE_6__ {TYPE_1__ hdr; } ;
struct uni_all {TYPE_2__ u; } ;
struct TYPE_8__ {scalar_t__ q2932; } ;
struct uni {TYPE_4__ cx; int /*<<< orphan*/  cause; } ;
struct call {scalar_t__ type; } ;

/* Variables and functions */
 scalar_t__ CALL_COBI ; 
 scalar_t__ CREF_DUMMY ; 
 scalar_t__ CREF_GLOBAL ; 
 struct uni_all* UNI_ALLOC () ; 
 int /*<<< orphan*/  UNI_FAC_COORD ; 
 int /*<<< orphan*/  UNI_FREE (struct uni_all*) ; 
 int /*<<< orphan*/  VERBOSE (struct uni*,int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  input_call (struct call*,struct uni_msg*,struct uni_all*) ; 
 int /*<<< orphan*/  input_cobi (struct call*,struct uni_msg*,struct uni_all*) ; 
 int /*<<< orphan*/  input_dummy (struct uni*,struct uni_msg*,struct uni_all*) ; 
 int /*<<< orphan*/  input_global (struct uni*,struct uni_msg*,struct uni_all*) ; 
 int /*<<< orphan*/  input_unknown (struct uni*,struct uni_msg*,struct uni_all*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 scalar_t__ uni_decode_head (struct uni_msg*,struct uni_all*,TYPE_4__*) ; 
 struct call* uni_find_call (struct uni*,TYPE_3__*) ; 
 int /*<<< orphan*/  uni_msg_destroy (struct uni_msg*) ; 

__attribute__((used)) static void
coord_saal_data_indication(struct uni *uni, struct uni_msg *m)
{
	struct uni_all *u;
	struct call *c;

	memset(&uni->cause, 0, sizeof(uni->cause));
	if ((u = UNI_ALLOC()) == NULL) {
		uni_msg_destroy(m);
		return;
	}
	if (uni_decode_head(m, u, &uni->cx)) {
		VERBOSE(uni, UNI_FAC_COORD, 2, "bogus message - ignored");
		uni_msg_destroy(m);
		UNI_FREE(u);
		return;
	}
	if (u->u.hdr.cref.cref == CREF_DUMMY) {
		if (uni->cx.q2932) {
			input_dummy(uni, m, u);
		} else {
			VERBOSE(uni, UNI_FAC_COORD, 2, "dummy cref - ignored");
			UNI_FREE(u);
			uni_msg_destroy(m);
		}
		return;
	}

	if (u->u.hdr.cref.cref == CREF_GLOBAL)
		input_global(uni, m, u);
	else if ((c = uni_find_call(uni, &u->u.hdr.cref)) == NULL)
		input_unknown(uni, m, u);
	else if (c->type == CALL_COBI)
		input_cobi(c, m, u);
	else
		input_call(c, m, u);
}