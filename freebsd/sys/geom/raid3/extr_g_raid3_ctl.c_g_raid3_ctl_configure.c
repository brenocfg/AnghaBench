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
typedef  size_t u_int ;
struct gctl_req {int dummy; } ;
struct g_raid3_softc {scalar_t__ sc_ndisks; int sc_flags; int /*<<< orphan*/  sc_lock; struct g_raid3_disk* sc_disks; } ;
struct g_raid3_disk {scalar_t__ d_state; int /*<<< orphan*/  d_flags; } ;
struct g_class {int dummy; } ;

/* Variables and functions */
 int G_RAID3_DEVICE_FLAG_NOAUTOSYNC ; 
 int G_RAID3_DEVICE_FLAG_NOFAILSYNC ; 
 int G_RAID3_DEVICE_FLAG_ROUND_ROBIN ; 
 int G_RAID3_DEVICE_FLAG_VERIFY ; 
 int /*<<< orphan*/  G_RAID3_DISK_FLAG_DIRTY ; 
 int /*<<< orphan*/  G_RAID3_DISK_FLAG_FORCE_SYNC ; 
 int /*<<< orphan*/  G_RAID3_DISK_STATE_DISCONNECTED ; 
 scalar_t__ G_RAID3_DISK_STATE_STALE ; 
 scalar_t__ G_RAID3_DISK_STATE_SYNCHRONIZING ; 
 int /*<<< orphan*/  G_RAID3_EVENT_DONTWAIT ; 
 int /*<<< orphan*/  g_raid3_event_send (struct g_raid3_disk*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct g_raid3_softc* g_raid3_find_device (struct g_class*,char const*) ; 
 scalar_t__ g_raid3_ndisks (struct g_raid3_softc*,int) ; 
 int /*<<< orphan*/  g_raid3_update_metadata (struct g_raid3_disk*) ; 
 int /*<<< orphan*/  gctl_error (struct gctl_req*,char*,...) ; 
 char* gctl_get_asciiparam (struct gctl_req*,char*) ; 
 int* gctl_get_paraml (struct gctl_req*,char*,int) ; 
 int /*<<< orphan*/  sx_xunlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
g_raid3_ctl_configure(struct gctl_req *req, struct g_class *mp)
{
	struct g_raid3_softc *sc;
	struct g_raid3_disk *disk;
	const char *name;
	int *nargs, do_sync = 0, dirty = 1;
	int *autosync, *noautosync;
	int *failsync, *nofailsync;
	int *round_robin, *noround_robin;
	int *verify, *noverify;
	u_int n;

	nargs = gctl_get_paraml(req, "nargs", sizeof(*nargs));
	if (nargs == NULL) {
		gctl_error(req, "No '%s' argument.", "nargs");
		return;
	}
	if (*nargs != 1) {
		gctl_error(req, "Invalid number of arguments.");
		return;
	}
	autosync = gctl_get_paraml(req, "autosync", sizeof(*autosync));
	if (autosync == NULL) {
		gctl_error(req, "No '%s' argument.", "autosync");
		return;
	}
	noautosync = gctl_get_paraml(req, "noautosync", sizeof(*noautosync));
	if (noautosync == NULL) {
		gctl_error(req, "No '%s' argument.", "noautosync");
		return;
	}
	if (*autosync && *noautosync) {
		gctl_error(req, "'%s' and '%s' specified.", "autosync",
		    "noautosync");
		return;
	}
	failsync = gctl_get_paraml(req, "failsync", sizeof(*failsync));
	if (failsync == NULL) {
		gctl_error(req, "No '%s' argument.", "failsync");
		return;
	}
	nofailsync = gctl_get_paraml(req, "nofailsync", sizeof(*nofailsync));
	if (nofailsync == NULL) {
		gctl_error(req, "No '%s' argument.", "nofailsync");
		return;
	}
	if (*failsync && *nofailsync) {
		gctl_error(req, "'%s' and '%s' specified.", "failsync",
		    "nofailsync");
		return;
	}
	round_robin = gctl_get_paraml(req, "round_robin", sizeof(*round_robin));
	if (round_robin == NULL) {
		gctl_error(req, "No '%s' argument.", "round_robin");
		return;
	}
	noround_robin = gctl_get_paraml(req, "noround_robin",
	    sizeof(*noround_robin));
	if (noround_robin == NULL) {
		gctl_error(req, "No '%s' argument.", "noround_robin");
		return;
	}
	if (*round_robin && *noround_robin) {
		gctl_error(req, "'%s' and '%s' specified.", "round_robin",
		    "noround_robin");
		return;
	}
	verify = gctl_get_paraml(req, "verify", sizeof(*verify));
	if (verify == NULL) {
		gctl_error(req, "No '%s' argument.", "verify");
		return;
	}
	noverify = gctl_get_paraml(req, "noverify", sizeof(*noverify));
	if (noverify == NULL) {
		gctl_error(req, "No '%s' argument.", "noverify");
		return;
	}
	if (*verify && *noverify) {
		gctl_error(req, "'%s' and '%s' specified.", "verify",
		    "noverify");
		return;
	}
	if (!*autosync && !*noautosync && !*failsync && !*nofailsync &&
	    !*round_robin && !*noround_robin && !*verify && !*noverify) {
		gctl_error(req, "Nothing has changed.");
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
	if (g_raid3_ndisks(sc, -1) < sc->sc_ndisks) {
		gctl_error(req, "Not all disks connected.");
		sx_xunlock(&sc->sc_lock);
		return;
	}
	if ((sc->sc_flags & G_RAID3_DEVICE_FLAG_NOAUTOSYNC) != 0) {
		if (*autosync) {
			sc->sc_flags &= ~G_RAID3_DEVICE_FLAG_NOAUTOSYNC;
			do_sync = 1;
		}
	} else {
		if (*noautosync)
			sc->sc_flags |= G_RAID3_DEVICE_FLAG_NOAUTOSYNC;
	}
	if ((sc->sc_flags & G_RAID3_DEVICE_FLAG_NOFAILSYNC) != 0) {
		if (*failsync)
			sc->sc_flags &= ~G_RAID3_DEVICE_FLAG_NOFAILSYNC;
	} else {
		if (*nofailsync) {
			sc->sc_flags |= G_RAID3_DEVICE_FLAG_NOFAILSYNC;
			dirty = 0;
		}
	}
	if ((sc->sc_flags & G_RAID3_DEVICE_FLAG_VERIFY) != 0) {
		if (*noverify)
			sc->sc_flags &= ~G_RAID3_DEVICE_FLAG_VERIFY;
	} else {
		if (*verify)
			sc->sc_flags |= G_RAID3_DEVICE_FLAG_VERIFY;
	}
	if ((sc->sc_flags & G_RAID3_DEVICE_FLAG_ROUND_ROBIN) != 0) {
		if (*noround_robin)
			sc->sc_flags &= ~G_RAID3_DEVICE_FLAG_ROUND_ROBIN;
	} else {
		if (*round_robin)
			sc->sc_flags |= G_RAID3_DEVICE_FLAG_ROUND_ROBIN;
	}
	if ((sc->sc_flags & G_RAID3_DEVICE_FLAG_VERIFY) != 0 &&
	    (sc->sc_flags & G_RAID3_DEVICE_FLAG_ROUND_ROBIN) != 0) {
		/*
		 * VERIFY and ROUND-ROBIN options are mutally exclusive.
		 */
		sc->sc_flags &= ~G_RAID3_DEVICE_FLAG_ROUND_ROBIN;
	}
	for (n = 0; n < sc->sc_ndisks; n++) {
		disk = &sc->sc_disks[n];
		if (do_sync) {
			if (disk->d_state == G_RAID3_DISK_STATE_SYNCHRONIZING)
				disk->d_flags &= ~G_RAID3_DISK_FLAG_FORCE_SYNC;
		}
		if (!dirty)
			disk->d_flags &= ~G_RAID3_DISK_FLAG_DIRTY;
		g_raid3_update_metadata(disk);
		if (do_sync) {
			if (disk->d_state == G_RAID3_DISK_STATE_STALE) {
				/*
				 * XXX: This is probably possible that this
				 *      component will not be retasted.
				 */
				g_raid3_event_send(disk,
				    G_RAID3_DISK_STATE_DISCONNECTED,
				    G_RAID3_EVENT_DONTWAIT);
			}
		}
	}
	sx_xunlock(&sc->sc_lock);
}