#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  cause; } ;
struct TYPE_5__ {TYPE_1__ add_party_rej; } ;
struct uni_all {TYPE_2__ u; } ;
struct call {scalar_t__ cstate; TYPE_3__* uni; } ;
struct TYPE_6__ {int /*<<< orphan*/  cause; } ;

/* Variables and functions */
 scalar_t__ CALLST_N12 ; 
 scalar_t__ CALLST_U11 ; 
 int /*<<< orphan*/  UNI_FREE (struct uni_all*) ; 
 int /*<<< orphan*/  clear_callD (struct call*) ; 
 scalar_t__ uni_party_act_count (struct call*,int) ; 
 int /*<<< orphan*/  uni_send_output (struct uni_all*,TYPE_3__*) ; 

__attribute__((used)) static void
unx_send_add_party_rej(struct call *c, struct uni_all *u)
{

	if (uni_party_act_count(c, 2) == 0) {
		if (c->cstate != CALLST_U11 && c->cstate != CALLST_N12) {
			c->uni->cause = u->u.add_party_rej.cause;
			clear_callD(c);
		}
	} else
		(void)uni_send_output(u, c->uni);
	UNI_FREE(u);
}