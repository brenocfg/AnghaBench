#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  mtx; } ;
struct mxge_slice_state {TYPE_1__ tx; } ;
struct ifnet {TYPE_2__* if_softc; } ;
struct TYPE_4__ {struct mxge_slice_state* ss; } ;
typedef  TYPE_2__ mxge_softc_t ;

/* Variables and functions */
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mxge_start_locked (struct mxge_slice_state*) ; 

__attribute__((used)) static void
mxge_start(struct ifnet *ifp)
{
	mxge_softc_t *sc = ifp->if_softc;
	struct mxge_slice_state *ss;

	/* only use the first slice for now */
	ss = &sc->ss[0];
	mtx_lock(&ss->tx.mtx);
	mxge_start_locked(ss);
	mtx_unlock(&ss->tx.mtx);		
}