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
struct ccsig {scalar_t__ type; int /*<<< orphan*/  arg1; scalar_t__ has_msg; int /*<<< orphan*/  arg2; int /*<<< orphan*/  sig; int /*<<< orphan*/  target; } ;
struct ccdata {int /*<<< orphan*/  free_sigs; int /*<<< orphan*/  sigs; } ;

/* Variables and functions */
 scalar_t__ SIG_USER ; 
 struct ccsig* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_INSERT_HEAD (int /*<<< orphan*/ *,struct ccsig*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct ccsig*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cc_conn_sig_handle (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cc_sig_log (struct ccdata*,char*,char*) ; 
 int /*<<< orphan*/  cc_user_sig_handle (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  link ; 
 int /*<<< orphan*/  uni_msg_destroy (int /*<<< orphan*/ ) ; 

void
cc_work(struct ccdata *cc)
{
	struct ccsig *s;

	cc_sig_log(cc, "start %s", "work");
	while ((s = TAILQ_FIRST(&cc->sigs)) != NULL) {
		TAILQ_REMOVE(&cc->sigs, s, link);
		if (s->type == SIG_USER)
			cc_user_sig_handle(s->target, s->sig, s->arg1, s->arg2);
		else {
			cc_conn_sig_handle(s->target, s->sig, s->arg1, s->arg2);
			if (s->has_msg)
				uni_msg_destroy(s->arg1);
		}
		TAILQ_INSERT_HEAD(&cc->free_sigs, s, link);
	}
	cc_sig_log(cc, "end %s", "work");
}