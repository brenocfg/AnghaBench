#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u_int ;
struct gctl_req {int dummy; } ;
struct g_provider {char const* name; } ;
struct g_mirror_softc {int sc_flags; int /*<<< orphan*/  sc_lock; TYPE_1__* sc_geom; } ;
struct g_mirror_metadata {int dummy; } ;
struct TYPE_5__ {scalar_t__ ds_syncid; } ;
struct g_mirror_disk {scalar_t__ d_state; TYPE_3__* d_consumer; int /*<<< orphan*/  d_flags; TYPE_2__ d_sync; } ;
struct g_class {int dummy; } ;
typedef  int /*<<< orphan*/  param ;
struct TYPE_6__ {struct g_provider* provider; } ;
struct TYPE_4__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int G_MIRROR_DEVICE_FLAG_NOAUTOSYNC ; 
 int /*<<< orphan*/  G_MIRROR_DISK_FLAG_FORCE_SYNC ; 
 scalar_t__ G_MIRROR_DISK_STATE_ACTIVE ; 
 int /*<<< orphan*/  G_MIRROR_DISK_STATE_DISCONNECTED ; 
 int /*<<< orphan*/  G_MIRROR_EVENT_WAIT ; 
 int g_mirror_add_disk (struct g_mirror_softc*,struct g_provider*,struct g_mirror_metadata*) ; 
 int /*<<< orphan*/  g_mirror_event_send (struct g_mirror_disk*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct g_mirror_softc* g_mirror_find_device (struct g_class*,char const*) ; 
 struct g_mirror_disk* g_mirror_find_disk (struct g_mirror_softc*,char const*) ; 
 int g_mirror_ndisks (struct g_mirror_softc*,scalar_t__) ; 
 int g_mirror_read_metadata (TYPE_3__*,struct g_mirror_metadata*) ; 
 int /*<<< orphan*/  g_mirror_update_metadata (struct g_mirror_disk*) ; 
 int /*<<< orphan*/  g_topology_lock () ; 
 int /*<<< orphan*/  g_topology_unlock () ; 
 int /*<<< orphan*/  gctl_error (struct gctl_req*,char*,...) ; 
 char* gctl_get_asciiparam (struct gctl_req*,char*) ; 
 int* gctl_get_paraml (struct gctl_req*,char*,int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 
 int /*<<< orphan*/  sx_xunlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
g_mirror_ctl_rebuild(struct gctl_req *req, struct g_class *mp)
{
	struct g_mirror_metadata md;
	struct g_mirror_softc *sc;
	struct g_mirror_disk *disk;
	struct g_provider *pp;
	const char *name;
	char param[16];
	int error, *nargs;
	u_int i;

	nargs = gctl_get_paraml(req, "nargs", sizeof(*nargs));
	if (nargs == NULL) {
		gctl_error(req, "No '%s' argument.", "nargs");
		return;
	}
	if (*nargs < 2) {
		gctl_error(req, "Too few arguments.");
		return;
	}
	name = gctl_get_asciiparam(req, "arg0");
	if (name == NULL) {
		gctl_error(req, "No 'arg%u' argument.", 0);
		return;
	}
	sc = g_mirror_find_device(mp, name);
	if (sc == NULL) {
		gctl_error(req, "No such device: %s.", name);
		return;
	}
	for (i = 1; i < (u_int)*nargs; i++) {
		snprintf(param, sizeof(param), "arg%u", i);
		name = gctl_get_asciiparam(req, param);
		if (name == NULL) {
			gctl_error(req, "No 'arg%u' argument.", i);
			continue;
		}
		disk = g_mirror_find_disk(sc, name);
		if (disk == NULL) {
			gctl_error(req, "No such provider: %s.", name);
			continue;
		}
		if (g_mirror_ndisks(sc, G_MIRROR_DISK_STATE_ACTIVE) == 1 &&
		    disk->d_state == G_MIRROR_DISK_STATE_ACTIVE) {
			/*
			 * This is the last active disk. There will be nothing
			 * to rebuild it from, so deny this request.
			 */
			gctl_error(req,
			    "Provider %s is the last active provider in %s.",
			    name, sc->sc_geom->name);
			break;
		}
		/*
		 * Do rebuild by resetting syncid, disconnecting the disk and
		 * connecting it again.
		 */
		disk->d_sync.ds_syncid = 0;
		if ((sc->sc_flags & G_MIRROR_DEVICE_FLAG_NOAUTOSYNC) != 0)
			disk->d_flags |= G_MIRROR_DISK_FLAG_FORCE_SYNC;
		g_mirror_update_metadata(disk);
		pp = disk->d_consumer->provider;
		g_topology_lock();
		error = g_mirror_read_metadata(disk->d_consumer, &md);
		g_topology_unlock();
		g_mirror_event_send(disk, G_MIRROR_DISK_STATE_DISCONNECTED,
		    G_MIRROR_EVENT_WAIT);
		if (error != 0) {
			gctl_error(req, "Cannot read metadata from %s.",
			    pp->name);
			continue;
		}
		error = g_mirror_add_disk(sc, pp, &md);
		if (error != 0) {
			gctl_error(req, "Cannot reconnect component %s.",
			    pp->name);
			continue;
		}
	}
	sx_xunlock(&sc->sc_lock);
}