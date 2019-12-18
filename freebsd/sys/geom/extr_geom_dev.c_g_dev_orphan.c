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
struct g_dev_softc {struct cdev* sc_dev; } ;
struct g_consumer {TYPE_1__* geom; struct g_dev_softc* private; } ;
struct diocskerneldump_arg {int /*<<< orphan*/  kda_index; } ;
struct cdev {int si_flags; } ;
typedef  int /*<<< orphan*/  kda ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  G_T_TOPOLOGY ; 
 int /*<<< orphan*/  KDA_REMOVE_DEV ; 
 int SI_DUMPDEV ; 
 int /*<<< orphan*/  bzero (struct diocskerneldump_arg*,int) ; 
 int /*<<< orphan*/  delist_dev (struct cdev*) ; 
 int /*<<< orphan*/  destroy_dev_sched_cb (struct cdev*,int /*<<< orphan*/ ,struct g_consumer*) ; 
 int /*<<< orphan*/  devtoname (struct cdev*) ; 
 int /*<<< orphan*/  dumper_remove (int /*<<< orphan*/ ,struct diocskerneldump_arg*) ; 
 int /*<<< orphan*/  g_dev_callback ; 
 int /*<<< orphan*/  g_topology_assert () ; 
 int /*<<< orphan*/  g_trace (int /*<<< orphan*/ ,char*,struct g_consumer*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
g_dev_orphan(struct g_consumer *cp)
{
	struct cdev *dev;
	struct g_dev_softc *sc;

	g_topology_assert();
	sc = cp->private;
	dev = sc->sc_dev;
	g_trace(G_T_TOPOLOGY, "g_dev_orphan(%p(%s))", cp, cp->geom->name);

	/* Reset any dump-area set on this device */
	if (dev->si_flags & SI_DUMPDEV) {
		struct diocskerneldump_arg kda;

		bzero(&kda, sizeof(kda));
		kda.kda_index = KDA_REMOVE_DEV;
		(void)dumper_remove(devtoname(dev), &kda);
	}

	/* Destroy the struct cdev *so we get no more requests */
	delist_dev(dev);
	destroy_dev_sched_cb(dev, g_dev_callback, cp);
}