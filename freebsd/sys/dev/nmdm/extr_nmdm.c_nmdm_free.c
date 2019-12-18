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
struct nmdmsoftc {int /*<<< orphan*/  ns_mtx; } ;
struct nmdmpart {TYPE_1__* np_other; int /*<<< orphan*/  np_task; int /*<<< orphan*/  np_callout; struct nmdmsoftc* np_pair; } ;
struct TYPE_2__ {int /*<<< orphan*/ * np_other; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_NMDM ; 
 int /*<<< orphan*/  atomic_subtract_int (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  callout_drain (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (struct nmdmsoftc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nmdm_count ; 
 int /*<<< orphan*/  taskqueue_drain (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  taskqueue_swi ; 

__attribute__((used)) static void
nmdm_free(void *softc)
{
	struct nmdmpart *np = (struct nmdmpart *)softc;
	struct nmdmsoftc *ns = np->np_pair;

	callout_drain(&np->np_callout);
	taskqueue_drain(taskqueue_swi, &np->np_task);

	/*
	 * The function is called on both parts simultaneously.  We serialize
	 * with help of ns_mtx.  The first invocation should return and
	 * delegate freeing of resources to the second.
	 */
	mtx_lock(&ns->ns_mtx);
	if (np->np_other != NULL) {
		np->np_other->np_other = NULL;
		mtx_unlock(&ns->ns_mtx);
		return;
	}
	mtx_destroy(&ns->ns_mtx);
	free(ns, M_NMDM);
	atomic_subtract_int(&nmdm_count, 1);
}