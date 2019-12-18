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
struct g_raid3_softc {int /*<<< orphan*/  sc_lock; } ;
struct g_raid3_metadata {int dummy; } ;
struct g_raid3_disk {struct g_raid3_softc* d_softc; } ;

/* Variables and functions */
 int /*<<< orphan*/  G_RAID3_DEBUG (int,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  SX_LOCKED ; 
 int /*<<< orphan*/  g_raid3_fill_metadata (struct g_raid3_disk*,struct g_raid3_metadata*) ; 
 int /*<<< orphan*/  g_raid3_get_diskname (struct g_raid3_disk*) ; 
 int g_raid3_write_metadata (struct g_raid3_disk*,struct g_raid3_metadata*) ; 
 int /*<<< orphan*/  g_topology_assert_not () ; 
 int /*<<< orphan*/  sx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void
g_raid3_update_metadata(struct g_raid3_disk *disk)
{
	struct g_raid3_softc *sc;
	struct g_raid3_metadata md;
	int error;

	g_topology_assert_not();
	sc = disk->d_softc;
	sx_assert(&sc->sc_lock, SX_LOCKED);

	g_raid3_fill_metadata(disk, &md);
	error = g_raid3_write_metadata(disk, &md);
	if (error == 0) {
		G_RAID3_DEBUG(2, "Metadata on %s updated.",
		    g_raid3_get_diskname(disk));
	} else {
		G_RAID3_DEBUG(0,
		    "Cannot update metadata on disk %s (error=%d).",
		    g_raid3_get_diskname(disk), error);
	}
}