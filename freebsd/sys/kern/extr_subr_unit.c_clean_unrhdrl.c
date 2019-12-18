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
struct unrhdr {int /*<<< orphan*/  mtx; int /*<<< orphan*/  ppfree; } ;
struct unr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  Free (struct unr*) ; 
 int /*<<< orphan*/  MA_OWNED ; 
 struct unr* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct unr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list ; 
 int /*<<< orphan*/  mtx_assert (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ ) ; 

void
clean_unrhdrl(struct unrhdr *uh)
{
	struct unr *up;

	mtx_assert(uh->mtx, MA_OWNED);
	while ((up = TAILQ_FIRST(&uh->ppfree)) != NULL) {
		TAILQ_REMOVE(&uh->ppfree, up, list);
		mtx_unlock(uh->mtx);
		Free(up);
		mtx_lock(uh->mtx);
	}

}