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
struct uni_msg {int dummy; } ;
struct ccsig {scalar_t__ arg1; scalar_t__ has_msg; } ;
struct ccdata {int /*<<< orphan*/  free_sigs; int /*<<< orphan*/  def_sigs; int /*<<< orphan*/  sigs; } ;

/* Variables and functions */
 int /*<<< orphan*/  CCFREE (struct ccsig*) ; 
 struct ccsig* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct ccsig*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  link ; 
 int /*<<< orphan*/  uni_msg_destroy (struct uni_msg*) ; 

void
cc_sig_flush_all(struct ccdata *cc)
{
	struct ccsig *s;

	while ((s = TAILQ_FIRST(&cc->sigs)) != NULL) {
		if (s->has_msg)
			uni_msg_destroy((struct uni_msg *)s->arg1);
		TAILQ_REMOVE(&cc->sigs, s, link);
		CCFREE(s);
	}
	while ((s = TAILQ_FIRST(&cc->def_sigs)) != NULL) {
		if (s->has_msg)
			uni_msg_destroy((struct uni_msg *)s->arg1);
		TAILQ_REMOVE(&cc->def_sigs, s, link);
		CCFREE(s);
	}
	while ((s = TAILQ_FIRST(&cc->free_sigs)) != NULL) {
		TAILQ_REMOVE(&cc->free_sigs, s, link);
		CCFREE(s);
	}
}