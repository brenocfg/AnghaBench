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
struct cdev {char* si_name; } ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  M_WAITOK ; 
 int /*<<< orphan*/  SPECNAMELEN ; 
 int /*<<< orphan*/  devctl_notify_f (char*,char*,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*) ; 

__attribute__((used)) static void
g_dev_set_media(struct g_consumer *cp)
{
	struct g_dev_softc *sc;
	struct cdev *dev;
	char buf[SPECNAMELEN + 6];

	sc = cp->private;
	dev = sc->sc_dev;
	snprintf(buf, sizeof(buf), "cdev=%s", dev->si_name);
	devctl_notify_f("DEVFS", "CDEV", "MEDIACHANGE", buf, M_WAITOK);
	devctl_notify_f("GEOM", "DEV", "MEDIACHANGE", buf, M_WAITOK);
	dev = sc->sc_alias;
	if (dev != NULL) {
		snprintf(buf, sizeof(buf), "cdev=%s", dev->si_name);
		devctl_notify_f("DEVFS", "CDEV", "MEDIACHANGE", buf, M_WAITOK);
		devctl_notify_f("GEOM", "DEV", "MEDIACHANGE", buf, M_WAITOK);
	}
}