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
struct gctl_req {int dummy; } ;
struct g_raid3_softc {scalar_t__ sc_ndisks; int sc_flags; int /*<<< orphan*/  sc_lock; } ;
struct g_raid3_metadata {int dummy; } ;
struct TYPE_3__ {scalar_t__ ds_syncid; } ;
struct g_raid3_disk {scalar_t__ d_state; TYPE_2__* d_consumer; int /*<<< orphan*/  d_flags; TYPE_1__ d_sync; } ;
struct g_provider {char const* name; } ;
struct g_class {int dummy; } ;
struct TYPE_4__ {struct g_provider* provider; } ;

/* Variables and functions */
 int G_RAID3_DEVICE_FLAG_NOAUTOSYNC ; 
 int /*<<< orphan*/  G_RAID3_DISK_FLAG_FORCE_SYNC ; 
 scalar_t__ G_RAID3_DISK_STATE_ACTIVE ; 
 int /*<<< orphan*/  G_RAID3_DISK_STATE_DISCONNECTED ; 
 int /*<<< orphan*/  G_RAID3_EVENT_WAIT ; 
 int g_raid3_add_disk (struct g_raid3_softc*,struct g_provider*,struct g_raid3_metadata*) ; 
 int /*<<< orphan*/  g_raid3_event_send (struct g_raid3_disk*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct g_raid3_softc* g_raid3_find_device (struct g_class*,char const*) ; 
 struct g_raid3_disk* g_raid3_find_disk (struct g_raid3_softc*,char const*) ; 
 scalar_t__ g_raid3_ndisks (struct g_raid3_softc*,scalar_t__) ; 
 int g_raid3_read_metadata (TYPE_2__*,struct g_raid3_metadata*) ; 
 int /*<<< orphan*/  g_raid3_update_metadata (struct g_raid3_disk*) ; 
 int /*<<< orphan*/  g_topology_lock () ; 
 int /*<<< orphan*/  g_topology_unlock () ; 
 int /*<<< orphan*/  gctl_error (struct gctl_req*,char*,...) ; 
 char* gctl_get_asciiparam (struct gctl_req*,char*) ; 
 int* gctl_get_paraml (struct gctl_req*,char*,int) ; 
 int /*<<< orphan*/  sx_xunlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
g_raid3_ctl_rebuild(struct gctl_req *req, struct g_class *mp)
{
	struct g_raid3_metadata md;
	struct g_raid3_softc *sc;
	struct g_raid3_disk *disk;
	struct g_provider *pp;
	const char *name;
	int error, *nargs;

	nargs = gctl_get_paraml(req, "nargs", sizeof(*nargs));
	if (nargs == NULL) {
		gctl_error(req, "No '%s' argument.", "nargs");
		return;
	}
	if (*nargs != 2) {
		gctl_error(req, "Invalid number of arguments.");
		return;
	}
	name = gctl_get_asciiparam(req, "arg0");
	if (name == NULL) {
		gctl_error(req, "No 'arg%u' argument.", 0);
		return;
	}
	sc = g_raid3_find_device(mp, name);
	if (sc == NULL) {
		gctl_error(req, "No such device: %s.", name);
		return;
	}
	name = gctl_get_asciiparam(req, "arg1");
	if (name == NULL) {
		gctl_error(req, "No 'arg%u' argument.", 1);
		sx_xunlock(&sc->sc_lock);
		return;
	}
	disk = g_raid3_find_disk(sc, name);
	if (disk == NULL) {
		gctl_error(req, "No such provider: %s.", name);
		sx_xunlock(&sc->sc_lock);
		return;
	}
	if (disk->d_state == G_RAID3_DISK_STATE_ACTIVE &&
	    g_raid3_ndisks(sc, G_RAID3_DISK_STATE_ACTIVE) < sc->sc_ndisks) {
		gctl_error(req, "There is one stale disk already.");
		sx_xunlock(&sc->sc_lock);
		return;
	}
	/*
	 * Do rebuild by resetting syncid and disconnecting disk.
	 * It'll be retasted, connected to the device and synchronized.
	 */
	disk->d_sync.ds_syncid = 0;
	if ((sc->sc_flags & G_RAID3_DEVICE_FLAG_NOAUTOSYNC) != 0)
		disk->d_flags |= G_RAID3_DISK_FLAG_FORCE_SYNC;
	g_raid3_update_metadata(disk);
	pp = disk->d_consumer->provider;
	g_topology_lock();
	error = g_raid3_read_metadata(disk->d_consumer, &md);
	g_topology_unlock();
	g_raid3_event_send(disk, G_RAID3_DISK_STATE_DISCONNECTED,
	    G_RAID3_EVENT_WAIT);
	if (error != 0) {
		gctl_error(req, "Cannot read metadata from %s.", pp->name);
		sx_xunlock(&sc->sc_lock);
		return;
	}
	error = g_raid3_add_disk(sc, pp, &md);
	if (error != 0)
		gctl_error(req, "Cannot reconnect component %s.", pp->name);
	sx_xunlock(&sc->sc_lock);
}