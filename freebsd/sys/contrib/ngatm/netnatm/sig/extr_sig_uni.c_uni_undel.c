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
struct uni {int /*<<< orphan*/  workq; int /*<<< orphan*/  delq; } ;
struct sigqueue {int dummy; } ;
typedef  struct sig sig ;

/* Variables and functions */
 scalar_t__ TAILQ_EMPTY (int /*<<< orphan*/ *) ; 
 struct sig* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_INIT (struct sigqueue*) ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct sig*,int /*<<< orphan*/ ) ; 
 struct sig* TAILQ_NEXT (struct sig*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct sig*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  link ; 
 int stub1 (struct sig*,void*) ; 

void
uni_undel(struct uni *uni, int (*filter)(struct sig *, void *), void *arg)
{
	struct sigqueue		newq;
	struct sig *s, *s1;

	if (TAILQ_EMPTY(&uni->delq))
		return;

	TAILQ_INIT(&newq);

	s = TAILQ_FIRST(&uni->delq);
	while (s != NULL) {
		s1 = TAILQ_NEXT(s, link);
		if ((*filter)(s, arg)) {
			TAILQ_REMOVE(&uni->delq, s, link);
			TAILQ_INSERT_TAIL(&uni->workq, s, link);
		}
		s = s1;
	}
}