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
struct loginclass {int /*<<< orphan*/  lc_racct; int /*<<< orphan*/  lc_refcount; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_REMOVE (struct loginclass*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M_LOGINCLASS ; 
 int /*<<< orphan*/  free (struct loginclass*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lc_next ; 
 int /*<<< orphan*/  loginclasses_lock ; 
 int /*<<< orphan*/  racct_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  refcount_release (int /*<<< orphan*/ *) ; 
 scalar_t__ refcount_release_if_not_last (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rw_wlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rw_wunlock (int /*<<< orphan*/ *) ; 

void
loginclass_free(struct loginclass *lc)
{

	if (refcount_release_if_not_last(&lc->lc_refcount))
		return;

	rw_wlock(&loginclasses_lock);
	if (!refcount_release(&lc->lc_refcount)) {
		rw_wunlock(&loginclasses_lock);
		return;
	}

	racct_destroy(&lc->lc_racct);
	LIST_REMOVE(lc, lc_next);
	rw_wunlock(&loginclasses_lock);

	free(lc, M_LOGINCLASS);
}