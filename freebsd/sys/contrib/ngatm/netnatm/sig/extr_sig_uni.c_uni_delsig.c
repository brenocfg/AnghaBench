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
typedef  scalar_t__ u_int ;
struct uni {int /*<<< orphan*/  delq; int /*<<< orphan*/  workq; } ;
struct sig {scalar_t__ type; scalar_t__ u; scalar_t__ msg; struct party* party; struct call* call; } ;
struct party {int dummy; } ;
struct call {int dummy; } ;

/* Variables and functions */
 scalar_t__ SIG_CALL ; 
 int /*<<< orphan*/  SIG_FREE (struct sig*) ; 
 scalar_t__ SIG_PARTY ; 
 struct sig* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 struct sig* TAILQ_NEXT (struct sig*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct sig*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UNI_FREE (scalar_t__) ; 
 int /*<<< orphan*/  link ; 
 int /*<<< orphan*/  uni_msg_destroy (scalar_t__) ; 

void
uni_delsig(struct uni *uni, u_int type, struct call *c, struct party *p)
{
	struct sig *s, *s1;

	s = TAILQ_FIRST(&uni->workq);
	while (s != NULL) {
		s1 = TAILQ_NEXT(s, link);
		if ((type == SIG_CALL && s->type == SIG_CALL &&
		    s->call == c) ||
		    (type == SIG_PARTY && s->type == SIG_PARTY &&
		    s->call == c && s->party == p)) {
			TAILQ_REMOVE(&uni->workq, s, link);
			if (s->msg)
				uni_msg_destroy(s->msg);
			if (s->u)
				UNI_FREE(s->u);
			SIG_FREE(s);
		}
		s = s1;
	}

	s = TAILQ_FIRST(&uni->delq);
	while (s != NULL) {
		s1 = TAILQ_NEXT(s, link);
		if ((type == SIG_CALL && s->type == SIG_CALL &&
		    s->call == c) ||
		    (type == SIG_PARTY && s->type == SIG_PARTY &&
		    s->call == c && s->party == p)) {
			TAILQ_REMOVE(&uni->delq, s, link);
			if (s->msg)
				uni_msg_destroy(s->msg);
			if (s->u)
				UNI_FREE(s->u);
			SIG_FREE(s);						\
		}
		s = s1;
	}
}