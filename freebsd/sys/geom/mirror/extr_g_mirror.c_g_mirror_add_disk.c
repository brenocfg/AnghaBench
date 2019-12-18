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
struct g_provider {int /*<<< orphan*/  name; } ;
struct g_mirror_softc {scalar_t__ sc_genid; int /*<<< orphan*/  sc_name; } ;
struct g_mirror_metadata {scalar_t__ md_genid; scalar_t__ md_version; } ;
struct g_mirror_disk {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  G_MIRROR_DEBUG (int,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  G_MIRROR_DISK_STATE_NEW ; 
 int /*<<< orphan*/  G_MIRROR_EVENT_WAIT ; 
 scalar_t__ G_MIRROR_VERSION ; 
 int g_mirror_check_metadata (struct g_mirror_softc*,struct g_provider*,struct g_mirror_metadata*) ; 
 int g_mirror_event_send (struct g_mirror_disk*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct g_mirror_disk* g_mirror_init_disk (struct g_mirror_softc*,struct g_provider*,struct g_mirror_metadata*,int*) ; 
 int g_mirror_refresh_device (struct g_mirror_softc*,struct g_provider*,struct g_mirror_metadata*) ; 
 int /*<<< orphan*/  g_mirror_update_metadata (struct g_mirror_disk*) ; 
 int /*<<< orphan*/  g_topology_assert_not () ; 

int
g_mirror_add_disk(struct g_mirror_softc *sc, struct g_provider *pp,
    struct g_mirror_metadata *md)
{
	struct g_mirror_disk *disk;
	int error;

	g_topology_assert_not();
	G_MIRROR_DEBUG(2, "Adding disk %s.", pp->name);

	error = g_mirror_check_metadata(sc, pp, md);
	if (error != 0)
		return (error);

	if (md->md_genid < sc->sc_genid) {
		G_MIRROR_DEBUG(0, "Component %s (device %s) broken, skipping.",
		    pp->name, sc->sc_name);
		return (EINVAL);
	}

	/*
	 * If the component disk we're tasting has newer metadata than the
	 * STARTING gmirror device, refresh the device from the component.
	 */
	error = g_mirror_refresh_device(sc, pp, md);
	if (error != 0)
		return (error);

	disk = g_mirror_init_disk(sc, pp, md, &error);
	if (disk == NULL)
		return (error);
	error = g_mirror_event_send(disk, G_MIRROR_DISK_STATE_NEW,
	    G_MIRROR_EVENT_WAIT);
	if (error != 0)
		return (error);
	if (md->md_version < G_MIRROR_VERSION) {
		G_MIRROR_DEBUG(0, "Upgrading metadata on %s (v%d->v%d).",
		    pp->name, md->md_version, G_MIRROR_VERSION);
		g_mirror_update_metadata(disk);
	}
	return (0);
}