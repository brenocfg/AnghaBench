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
struct uni {int working; int /*<<< orphan*/  workq; } ;
struct sig {int type; int /*<<< orphan*/  u; int /*<<< orphan*/  msg; int /*<<< orphan*/  cookie; int /*<<< orphan*/  sig; int /*<<< orphan*/  party; int /*<<< orphan*/  call; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ,char*) ; 
#define  SIG_CALL 132 
#define  SIG_COORD 131 
 int /*<<< orphan*/  SIG_FREE (struct sig*) ; 
#define  SIG_PARTY 130 
#define  SIG_RESET_RESP 129 
#define  SIG_RESET_START 128 
 struct sig* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct sig*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  link ; 
 int /*<<< orphan*/  uni_sig_call (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uni_sig_coord (struct uni*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uni_sig_party (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uni_sig_respond (struct uni*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uni_sig_start (struct uni*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
uni_work(struct uni *uni)
{
	struct sig *s;

	if (uni->working)
		return;
	uni->working = 1;

	while ((s = TAILQ_FIRST(&uni->workq)) != NULL) {
		TAILQ_REMOVE(&uni->workq, s, link);
		switch (s->type) {

		  case SIG_COORD:
			uni_sig_coord(uni, s->sig, s->cookie, s->msg);
			break;

		  case SIG_RESET_START:
			uni_sig_start(uni, s->sig, s->cookie, s->msg, s->u);
			break;

		  case SIG_RESET_RESP:
			uni_sig_respond(uni, s->sig, s->cookie, s->msg, s->u);
			break;

		  case SIG_CALL:
			uni_sig_call(s->call, s->sig, s->cookie, s->msg, s->u);
			break;

		  case SIG_PARTY:
			uni_sig_party(s->party, s->sig, s->cookie, s->msg, s->u);
			break;

		  default:
			ASSERT(0, ("bad signal type"));
		}
		SIG_FREE(s);
	}

	uni->working = 0;
}