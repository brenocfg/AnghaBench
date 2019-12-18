#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  kfrwk_tq; int /*<<< orphan*/  kfrwk_testlist; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  KTFRWK_DESTROY () ; 
 int /*<<< orphan*/  KTFRWK_LOCK () ; 
 int /*<<< orphan*/  KTFRWK_UNLOCK () ; 
 int /*<<< orphan*/  TAILQ_EMPTY (int /*<<< orphan*/ *) ; 
 TYPE_1__ kfrwk ; 
 scalar_t__ ktest_frwk_inited ; 
 int /*<<< orphan*/  taskqueue_free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
kerntest_frwk_fini(void)
{
	KTFRWK_LOCK();
	if (!TAILQ_EMPTY(&kfrwk.kfrwk_testlist)) {
		/* Still modules registered */
		KTFRWK_UNLOCK();
		return (EBUSY);
	}
	ktest_frwk_inited = 0;
	KTFRWK_UNLOCK();
	taskqueue_free(kfrwk.kfrwk_tq);
	/* Ok lets destroy the mutex on the way outs */
	KTFRWK_DESTROY();
	return (0);
}