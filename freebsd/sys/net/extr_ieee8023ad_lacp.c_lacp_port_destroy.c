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
struct lagg_port {int /*<<< orphan*/  lp_detaching; } ;
struct lacp_softc {int dummy; } ;
struct lacp_port {int /*<<< orphan*/  lp_ifma; struct lacp_softc* lp_lsc; } ;

/* Variables and functions */
 int /*<<< orphan*/  LACP_LOCK (struct lacp_softc*) ; 
 int LACP_NTIMER ; 
 struct lacp_port* LACP_PORT (struct lagg_port*) ; 
 int /*<<< orphan*/  LACP_TIMER_DISARM (struct lacp_port*,int) ; 
 int /*<<< orphan*/  LACP_UNLOCK (struct lacp_softc*) ; 
 int /*<<< orphan*/  LIST_REMOVE (struct lacp_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int /*<<< orphan*/  free (struct lacp_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_delmulti_ifma (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lacp_disable_collecting (struct lacp_port*) ; 
 int /*<<< orphan*/  lacp_disable_distributing (struct lacp_port*) ; 
 int /*<<< orphan*/  lacp_unselect (struct lacp_port*) ; 
 int /*<<< orphan*/  lp_next ; 

void
lacp_port_destroy(struct lagg_port *lgp)
{
	struct lacp_port *lp = LACP_PORT(lgp);
	struct lacp_softc *lsc = lp->lp_lsc;
	int i;

	LACP_LOCK(lsc);
	for (i = 0; i < LACP_NTIMER; i++) {
		LACP_TIMER_DISARM(lp, i);
	}

	lacp_disable_collecting(lp);
	lacp_disable_distributing(lp);
	lacp_unselect(lp);

	LIST_REMOVE(lp, lp_next);
	LACP_UNLOCK(lsc);

	/* The address may have already been removed by if_purgemaddrs() */
	if (!lgp->lp_detaching)
		if_delmulti_ifma(lp->lp_ifma);

	free(lp, M_DEVBUF);
}