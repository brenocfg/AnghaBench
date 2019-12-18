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
struct uni_msg {int dummy; } ;
struct ccsig {scalar_t__ type; void* target; scalar_t__ arg1; scalar_t__ has_msg; } ;
struct ccdata {int /*<<< orphan*/  free_sigs; int /*<<< orphan*/  def_sigs; int /*<<< orphan*/  sigs; } ;

/* Variables and functions */
 struct ccsig* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_INSERT_HEAD (int /*<<< orphan*/ *,struct ccsig*,int /*<<< orphan*/ ) ; 
 struct ccsig* TAILQ_NEXT (struct ccsig*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct ccsig*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  link ; 
 int /*<<< orphan*/  uni_msg_destroy (struct uni_msg*) ; 

__attribute__((used)) static /* __inline */ void
sig_flush(struct ccdata *cc, u_int type, void *target)
{
	struct ccsig *s, *s1;

	s = TAILQ_FIRST(&cc->sigs);
	while (s != NULL) {
		s1 = TAILQ_NEXT(s, link);
		if (s->type == type && s->target == target) {
			if (s->has_msg)
				uni_msg_destroy((struct uni_msg *)s->arg1);
			TAILQ_REMOVE(&cc->sigs, s, link);
			TAILQ_INSERT_HEAD(&cc->free_sigs, s, link);
		}
		s = s1;
	}

	s = TAILQ_FIRST(&cc->def_sigs);
	while (s != NULL) {
		s1 = TAILQ_NEXT(s, link);
		if (s->type == type && s->target == target) {
			if (s->has_msg)
				uni_msg_destroy((struct uni_msg *)s->arg1);
			TAILQ_REMOVE(&cc->def_sigs, s, link);
			TAILQ_INSERT_HEAD(&cc->free_sigs, s, link);
		}
		s = s1;
	}
}