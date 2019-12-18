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
struct g_provider {int error; int flags; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int G_PF_ORPHAN ; 
 int /*<<< orphan*/  G_T_TOPOLOGY ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct g_provider*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_doorstep ; 
 int /*<<< orphan*/  g_eventlock ; 
 int /*<<< orphan*/  g_trace (int /*<<< orphan*/ ,char*,struct g_provider*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  g_wait_event ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  orphan ; 
 int /*<<< orphan*/  wakeup (int /*<<< orphan*/ *) ; 

void
g_orphan_provider(struct g_provider *pp, int error)
{

	/* G_VALID_PROVIDER(pp)  We likely lack topology lock */
	g_trace(G_T_TOPOLOGY, "g_orphan_provider(%p(%s), %d)",
	    pp, pp->name, error);
	KASSERT(error != 0,
	    ("g_orphan_provider(%p(%s), 0) error must be non-zero\n",
	     pp, pp->name));
	
	pp->error = error;
	mtx_lock(&g_eventlock);
	KASSERT(!(pp->flags & G_PF_ORPHAN),
	    ("g_orphan_provider(%p(%s)), already an orphan", pp, pp->name));
	pp->flags |= G_PF_ORPHAN;
	TAILQ_INSERT_TAIL(&g_doorstep, pp, orphan);
	mtx_unlock(&g_eventlock);
	wakeup(&g_wait_event);
}