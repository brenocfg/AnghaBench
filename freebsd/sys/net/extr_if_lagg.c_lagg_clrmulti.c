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
struct lagg_port {scalar_t__ lp_detaching; int /*<<< orphan*/  lp_mc_head; int /*<<< orphan*/  lp_softc; } ;
struct lagg_mc {scalar_t__ mc_ifma; } ;

/* Variables and functions */
 int /*<<< orphan*/  LAGG_XLOCK_ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M_LAGG ; 
 struct lagg_mc* SLIST_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SLIST_REMOVE (int /*<<< orphan*/ *,struct lagg_mc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct lagg_mc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_delmulti_ifma (scalar_t__) ; 
 int /*<<< orphan*/  lagg_mc ; 
 int /*<<< orphan*/  mc_entries ; 

__attribute__((used)) static int
lagg_clrmulti(struct lagg_port *lp)
{
	struct lagg_mc *mc;

	LAGG_XLOCK_ASSERT(lp->lp_softc);
	while ((mc = SLIST_FIRST(&lp->lp_mc_head)) != NULL) {
		SLIST_REMOVE(&lp->lp_mc_head, mc, lagg_mc, mc_entries);
		if (mc->mc_ifma && lp->lp_detaching == 0)
			if_delmulti_ifma(mc->mc_ifma);
		free(mc, M_LAGG);
	}
	return (0);
}