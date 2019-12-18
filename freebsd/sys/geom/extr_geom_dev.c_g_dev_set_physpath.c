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
struct g_dev_softc {struct cdev* sc_alias; struct cdev* sc_dev; } ;
struct g_consumer {struct g_dev_softc* private; } ;
struct cdev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAKEDEV_WAITOK ; 
 int MAXPATHLEN ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int /*<<< orphan*/  destroy_dev (struct cdev*) ; 
 scalar_t__ g_access (struct g_consumer*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_free (char*) ; 
 int g_io_getattr (char*,struct g_consumer*,int*,char*) ; 
 char* g_malloc (int,int) ; 
 int /*<<< orphan*/  make_dev_physpath_alias (int /*<<< orphan*/ ,struct cdev**,struct cdev*,struct cdev*,char*) ; 
 scalar_t__ strlen (char*) ; 

__attribute__((used)) static void
g_dev_set_physpath(struct g_consumer *cp)
{
	struct g_dev_softc *sc;
	char *physpath;
	int error, physpath_len;

	if (g_access(cp, 1, 0, 0) != 0)
		return;

	sc = cp->private;
	physpath_len = MAXPATHLEN;
	physpath = g_malloc(physpath_len, M_WAITOK|M_ZERO);
	error = g_io_getattr("GEOM::physpath", cp, &physpath_len, physpath);
	g_access(cp, -1, 0, 0);
	if (error == 0 && strlen(physpath) != 0) {
		struct cdev *dev, *old_alias_dev;
		struct cdev **alias_devp;

		dev = sc->sc_dev;
		old_alias_dev = sc->sc_alias;
		alias_devp = (struct cdev **)&sc->sc_alias;
		make_dev_physpath_alias(MAKEDEV_WAITOK, alias_devp, dev,
		    old_alias_dev, physpath);
	} else if (sc->sc_alias) {
		destroy_dev((struct cdev *)sc->sc_alias);
		sc->sc_alias = NULL;
	}
	g_free(physpath);
}