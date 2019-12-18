#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  vdev_reopening; struct g_consumer* vdev_tsd; } ;
typedef  TYPE_2__ vdev_t ;
struct g_consumer {int flags; TYPE_1__* provider; } ;
struct TYPE_5__ {scalar_t__ error; } ;

/* Variables and functions */
 int /*<<< orphan*/  DROP_GIANT () ; 
 int G_CF_ORPHAN ; 
 int /*<<< orphan*/  PICKUP_GIANT () ; 
 int /*<<< orphan*/  g_topology_lock () ; 
 int /*<<< orphan*/  g_topology_unlock () ; 
 int /*<<< orphan*/  vdev_geom_close_locked (TYPE_2__*) ; 

__attribute__((used)) static void
vdev_geom_close(vdev_t *vd)
{
	struct g_consumer *cp;

	cp = vd->vdev_tsd;

	DROP_GIANT();
	g_topology_lock();

	if (!vd->vdev_reopening ||
	    (cp != NULL && ((cp->flags & G_CF_ORPHAN) != 0 ||
	    (cp->provider != NULL && cp->provider->error != 0))))
		vdev_geom_close_locked(vd);

	g_topology_unlock();
	PICKUP_GIANT();
}