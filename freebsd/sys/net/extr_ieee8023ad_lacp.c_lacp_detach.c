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
struct lacp_softc {int /*<<< orphan*/  lsc_callout; int /*<<< orphan*/  lsc_transit_callout; int /*<<< orphan*/ * lsc_active_aggregator; int /*<<< orphan*/  lsc_aggregators; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  LACP_LOCK_DESTROY (struct lacp_softc*) ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int /*<<< orphan*/  TAILQ_EMPTY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  callout_drain (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (struct lacp_softc*,int /*<<< orphan*/ ) ; 

void
lacp_detach(void *psc)
{
	struct lacp_softc *lsc = (struct lacp_softc *)psc;

	KASSERT(TAILQ_EMPTY(&lsc->lsc_aggregators),
	    ("aggregators still active"));
	KASSERT(lsc->lsc_active_aggregator == NULL,
	    ("aggregator still attached"));

	callout_drain(&lsc->lsc_transit_callout);
	callout_drain(&lsc->lsc_callout);

	LACP_LOCK_DESTROY(lsc);
	free(lsc, M_DEVBUF);
}