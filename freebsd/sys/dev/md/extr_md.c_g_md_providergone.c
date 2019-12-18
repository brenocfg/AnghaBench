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
struct md_s {int /*<<< orphan*/  queue_mtx; int /*<<< orphan*/  flags; } ;
struct g_provider {TYPE_1__* geom; } ;
struct TYPE_2__ {struct md_s* softc; } ;

/* Variables and functions */
 int /*<<< orphan*/  MD_PROVIDERGONE ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wakeup (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
g_md_providergone(struct g_provider *pp)
{
	struct md_s *sc = pp->geom->softc;

	mtx_lock(&sc->queue_mtx);
	sc->flags |= MD_PROVIDERGONE;
	wakeup(&sc->flags);
	mtx_unlock(&sc->queue_mtx);
}