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
struct g_provider {TYPE_1__* geom; int /*<<< orphan*/ * private; } ;
struct g_disk_softc {scalar_t__* led; int /*<<< orphan*/  start_mtx; int /*<<< orphan*/  done_mtx; int /*<<< orphan*/ * sysctl_tree; int /*<<< orphan*/  sysctl_ctx; struct disk* dp; } ;
struct disk {int /*<<< orphan*/  (* d_gone ) (struct disk*) ;} ;
struct TYPE_2__ {int /*<<< orphan*/ * softc; } ;

/* Variables and functions */
 int /*<<< orphan*/  g_free (struct g_disk_softc*) ; 
 int /*<<< orphan*/  led_set (scalar_t__*,char*) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct disk*) ; 
 int /*<<< orphan*/  sysctl_ctx_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
g_disk_providergone(struct g_provider *pp)
{
	struct disk *dp;
	struct g_disk_softc *sc;

	sc = (struct g_disk_softc *)pp->private;
	dp = sc->dp;
	if (dp != NULL && dp->d_gone != NULL)
		dp->d_gone(dp);
	if (sc->sysctl_tree != NULL) {
		sysctl_ctx_free(&sc->sysctl_ctx);
		sc->sysctl_tree = NULL;
	}
	if (sc->led[0] != 0) {
		led_set(sc->led, "0");
		sc->led[0] = 0;
	}
	pp->private = NULL;
	pp->geom->softc = NULL;
	mtx_destroy(&sc->done_mtx);
	mtx_destroy(&sc->start_mtx);
	g_free(sc);
}