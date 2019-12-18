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
struct thread {int dummy; } ;
struct g_dev_softc {scalar_t__ sc_open; int sc_active; int /*<<< orphan*/  sc_mtx; } ;
struct g_consumer {struct g_dev_softc* private; TYPE_1__* geom; } ;
struct cdev {struct g_consumer* si_drv2; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENXIO ; 
 int FREAD ; 
 int FWRITE ; 
 int /*<<< orphan*/  G_T_ACCESS ; 
 int O_EXCL ; 
 int SC_A_ACTIVE ; 
 int /*<<< orphan*/  SC_A_OPEN ; 
 int /*<<< orphan*/  atomic_clear_int (int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_set_int (int*,int /*<<< orphan*/ ) ; 
 int g_access (struct g_consumer*,int,int,int) ; 
 int /*<<< orphan*/  g_topology_lock () ; 
 int /*<<< orphan*/  g_topology_unlock () ; 
 int /*<<< orphan*/  g_trace (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int,int,struct thread*) ; 
 int hz ; 
 int /*<<< orphan*/  msleep (int*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
g_dev_close(struct cdev *dev, int flags, int fmt, struct thread *td)
{
	struct g_consumer *cp;
	struct g_dev_softc *sc;
	int error, r, w, e;

	cp = dev->si_drv2;
	if (cp == NULL)
		return (ENXIO);
	g_trace(G_T_ACCESS, "g_dev_close(%s, %d, %d, %p)",
	    cp->geom->name, flags, fmt, td);

	r = flags & FREAD ? -1 : 0;
	w = flags & FWRITE ? -1 : 0;
#ifdef notyet
	e = flags & O_EXCL ? -1 : 0;
#else
	e = 0;
#endif

	/*
	 * The vgonel(9) - caused by eg. forced unmount of devfs - calls
	 * VOP_CLOSE(9) on devfs vnode without any FREAD or FWRITE flags,
	 * which would result in zero deltas, which in turn would cause
	 * panic in g_access(9).
	 *
	 * Note that we cannot zero the counters (ie. do "r = cp->acr"
	 * etc) instead, because the consumer might be opened in another
	 * devfs instance.
	 */
	if (r + w + e == 0)
		return (EINVAL);

	sc = cp->private;
	mtx_lock(&sc->sc_mtx);
	sc->sc_open += r + w + e;
	if (sc->sc_open == 0)
		atomic_clear_int(&sc->sc_active, SC_A_OPEN);
	else
		atomic_set_int(&sc->sc_active, SC_A_OPEN);
	while (sc->sc_open == 0 && (sc->sc_active & SC_A_ACTIVE) != 0)
		msleep(&sc->sc_active, &sc->sc_mtx, 0, "g_dev_close", hz / 10);
	mtx_unlock(&sc->sc_mtx);
	g_topology_lock();
	error = g_access(cp, r, w, e);
	g_topology_unlock();
	return (error);
}