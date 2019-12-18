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
struct pass_softc {int flags; int /*<<< orphan*/  alias_dev; int /*<<< orphan*/  dev; } ;
struct mtx {int dummy; } ;
struct cam_periph {int flags; int /*<<< orphan*/  path; struct pass_softc* softc; } ;

/* Variables and functions */
 int CAM_PERIPH_INVALID ; 
 int /*<<< orphan*/  MAKEDEV_WAITOK ; 
 int /*<<< orphan*/  MAXPATHLEN ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int PASS_FLAG_INITIAL_PHYSPATH ; 
 struct mtx* cam_periph_mtx (struct cam_periph*) ; 
 int /*<<< orphan*/  cam_periph_release_locked (struct cam_periph*) ; 
 int /*<<< orphan*/  free (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  make_dev_physpath_alias (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 char* malloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (struct mtx*) ; 
 int /*<<< orphan*/  mtx_unlock (struct mtx*) ; 
 scalar_t__ strlen (char*) ; 
 scalar_t__ xpt_getattr (char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
pass_add_physpath(void *context, int pending)
{
	struct cam_periph *periph;
	struct pass_softc *softc;
	struct mtx *mtx;
	char *physpath;

	/*
	 * If we have one, create a devfs alias for our
	 * physical path.
	 */
	periph = context;
	softc = periph->softc;
	physpath = malloc(MAXPATHLEN, M_DEVBUF, M_WAITOK);
	mtx = cam_periph_mtx(periph);
	mtx_lock(mtx);

	if (periph->flags & CAM_PERIPH_INVALID)
		goto out;

	if (xpt_getattr(physpath, MAXPATHLEN,
			"GEOM::physpath", periph->path) == 0
	 && strlen(physpath) != 0) {

		mtx_unlock(mtx);
		make_dev_physpath_alias(MAKEDEV_WAITOK, &softc->alias_dev,
					softc->dev, softc->alias_dev, physpath);
		mtx_lock(mtx);
	}

out:
	/*
	 * Now that we've made our alias, we no longer have to have a
	 * reference to the device.
	 */
	if ((softc->flags & PASS_FLAG_INITIAL_PHYSPATH) == 0)
		softc->flags |= PASS_FLAG_INITIAL_PHYSPATH;

	/*
	 * We always acquire a reference to the periph before queueing this
	 * task queue function, so it won't go away before we run.
	 */
	while (pending-- > 0)
		cam_periph_release_locked(periph);
	mtx_unlock(mtx);

	free(physpath, M_DEVBUF);
}