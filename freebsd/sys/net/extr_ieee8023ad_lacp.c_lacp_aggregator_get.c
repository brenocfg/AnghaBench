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
struct lacp_softc {int /*<<< orphan*/  lsc_aggregators; } ;
struct lacp_port {int dummy; } ;
struct lacp_aggregator {int la_refcnt; scalar_t__ la_pending; int /*<<< orphan*/  la_ports; scalar_t__ la_nports; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_DEVBUF ; 
 int /*<<< orphan*/  M_NOWAIT ; 
 int /*<<< orphan*/  TAILQ_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct lacp_aggregator*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  la_q ; 
 struct lacp_aggregator* malloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct lacp_aggregator *
lacp_aggregator_get(struct lacp_softc *lsc, struct lacp_port *lp)
{
	struct lacp_aggregator *la;

	la = malloc(sizeof(*la), M_DEVBUF, M_NOWAIT);
	if (la) {
		la->la_refcnt = 1;
		la->la_nports = 0;
		TAILQ_INIT(&la->la_ports);
		la->la_pending = 0;
		TAILQ_INSERT_TAIL(&lsc->lsc_aggregators, la, la_q);
	}

	return (la);
}