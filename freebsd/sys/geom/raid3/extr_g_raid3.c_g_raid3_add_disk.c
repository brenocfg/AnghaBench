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
struct g_raid3_softc {scalar_t__ sc_state; scalar_t__ sc_genid; int /*<<< orphan*/  sc_name; } ;
struct g_raid3_metadata {scalar_t__ md_genid; scalar_t__ md_version; } ;
struct g_raid3_disk {int dummy; } ;
struct g_provider {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  G_RAID3_DEBUG (int,char*,int /*<<< orphan*/ ,...) ; 
 scalar_t__ G_RAID3_DEVICE_STATE_STARTING ; 
 int /*<<< orphan*/  G_RAID3_DISK_STATE_NEW ; 
 int /*<<< orphan*/  G_RAID3_EVENT_WAIT ; 
 scalar_t__ G_RAID3_VERSION ; 
 int g_raid3_check_metadata (struct g_raid3_softc*,struct g_provider*,struct g_raid3_metadata*) ; 
 int g_raid3_event_send (struct g_raid3_disk*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct g_raid3_disk* g_raid3_init_disk (struct g_raid3_softc*,struct g_provider*,struct g_raid3_metadata*,int*) ; 
 int /*<<< orphan*/  g_raid3_update_metadata (struct g_raid3_disk*) ; 
 int /*<<< orphan*/  g_topology_assert_not () ; 

int
g_raid3_add_disk(struct g_raid3_softc *sc, struct g_provider *pp,
    struct g_raid3_metadata *md)
{
	struct g_raid3_disk *disk;
	int error;

	g_topology_assert_not();
	G_RAID3_DEBUG(2, "Adding disk %s.", pp->name);

	error = g_raid3_check_metadata(sc, pp, md);
	if (error != 0)
		return (error);
	if (sc->sc_state != G_RAID3_DEVICE_STATE_STARTING &&
	    md->md_genid < sc->sc_genid) {
		G_RAID3_DEBUG(0, "Component %s (device %s) broken, skipping.",
		    pp->name, sc->sc_name);
		return (EINVAL);
	}
	disk = g_raid3_init_disk(sc, pp, md, &error);
	if (disk == NULL)
		return (error);
	error = g_raid3_event_send(disk, G_RAID3_DISK_STATE_NEW,
	    G_RAID3_EVENT_WAIT);
	if (error != 0)
		return (error);
	if (md->md_version < G_RAID3_VERSION) {
		G_RAID3_DEBUG(0, "Upgrading metadata on %s (v%d->v%d).",
		    pp->name, md->md_version, G_RAID3_VERSION);
		g_raid3_update_metadata(disk);
	}
	return (0);
}