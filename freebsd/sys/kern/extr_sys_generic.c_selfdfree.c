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
struct seltd {int /*<<< orphan*/  st_selq; } ;
struct selfd {int /*<<< orphan*/  sf_refs; int /*<<< orphan*/  sf_mtx; TYPE_1__* sf_si; } ;
struct TYPE_2__ {int /*<<< orphan*/  si_tdlist; } ;

/* Variables and functions */
 int /*<<< orphan*/  STAILQ_REMOVE (int /*<<< orphan*/ *,struct selfd*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct selfd*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ ) ; 
 scalar_t__ refcount_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  selfd ; 
 int /*<<< orphan*/  selfd_zone ; 
 int /*<<< orphan*/  sf_link ; 
 int /*<<< orphan*/  sf_threads ; 
 int /*<<< orphan*/  uma_zfree (int /*<<< orphan*/ ,struct selfd*) ; 

__attribute__((used)) static void
selfdfree(struct seltd *stp, struct selfd *sfp)
{
	STAILQ_REMOVE(&stp->st_selq, sfp, selfd, sf_link);
	if (sfp->sf_si != NULL) {
		mtx_lock(sfp->sf_mtx);
		if (sfp->sf_si != NULL) {
			TAILQ_REMOVE(&sfp->sf_si->si_tdlist, sfp, sf_threads);
			refcount_release(&sfp->sf_refs);
		}
		mtx_unlock(sfp->sf_mtx);
	}
	if (refcount_release(&sfp->sf_refs))
		uma_zfree(selfd_zone, sfp);
}