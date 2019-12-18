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
struct rlock {scalar_t__ rls_magic; int /*<<< orphan*/  rls_locks; } ;
struct rangelocks {scalar_t__ rls_magic; int /*<<< orphan*/  rls_locks; } ;

/* Variables and functions */
 int /*<<< orphan*/  PJDLOG_ASSERT (int) ; 
 scalar_t__ RANGELOCKS_MAGIC ; 
 struct rlock* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct rlock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct rlock*) ; 
 int /*<<< orphan*/  rl_next ; 

void
rangelock_free(struct rangelocks *rls)
{
	struct rlock *rl;

	PJDLOG_ASSERT(rls->rls_magic == RANGELOCKS_MAGIC);

	rls->rls_magic = 0;

	while ((rl = TAILQ_FIRST(&rls->rls_locks)) != NULL) {
		TAILQ_REMOVE(&rls->rls_locks, rl, rl_next);
		free(rl);
	}
	free(rls);
}