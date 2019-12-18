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
typedef  void* uint32_t ;
typedef  int /*<<< orphan*/  u_int ;
struct uni_msg {int dummy; } ;
struct uni_all {int dummy; } ;
struct uni {int /*<<< orphan*/  workq; } ;
struct sig {struct uni_all* u; struct party* party; struct call* call; struct uni_msg* msg; void* cookie; void* sig; int /*<<< orphan*/  type; } ;
struct party {int dummy; } ;
struct call {int dummy; } ;

/* Variables and functions */
 struct sig* SIG_ALLOC () ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct sig*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  link ; 

void
uni_enq_sig(struct uni *uni, u_int type, struct call *call,
    struct party *party, uint32_t sig, uint32_t cookie,
    struct uni_msg *msg, struct uni_all *u)
{
	struct sig *s;

	if ((s = SIG_ALLOC()) != NULL) {
		s->type = type;
		s->sig = sig;
		s->cookie = cookie;
		s->msg = msg;
		s->call = call;
		s->party = party;
		s->u = u;
		TAILQ_INSERT_TAIL(&uni->workq, s, link);
	}
}