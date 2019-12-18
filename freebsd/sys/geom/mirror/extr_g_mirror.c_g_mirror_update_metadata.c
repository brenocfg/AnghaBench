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
struct g_mirror_softc {scalar_t__ sc_type; int sc_flags; int /*<<< orphan*/  sc_lock; } ;
struct g_mirror_metadata {int dummy; } ;
struct g_mirror_disk {struct g_mirror_softc* d_softc; } ;

/* Variables and functions */
 int /*<<< orphan*/  G_MIRROR_DEBUG (int,char*,int /*<<< orphan*/ ,...) ; 
 int G_MIRROR_DEVICE_FLAG_WIPE ; 
 scalar_t__ G_MIRROR_TYPE_AUTOMATIC ; 
 int /*<<< orphan*/  SX_LOCKED ; 
 int /*<<< orphan*/  g_mirror_fill_metadata (struct g_mirror_softc*,struct g_mirror_disk*,struct g_mirror_metadata*) ; 
 int /*<<< orphan*/  g_mirror_get_diskname (struct g_mirror_disk*) ; 
 int g_mirror_write_metadata (struct g_mirror_disk*,struct g_mirror_metadata*) ; 
 int /*<<< orphan*/  g_topology_assert_not () ; 
 int /*<<< orphan*/  sx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void
g_mirror_update_metadata(struct g_mirror_disk *disk)
{
	struct g_mirror_softc *sc;
	struct g_mirror_metadata md;
	int error;

	g_topology_assert_not();
	sc = disk->d_softc;
	sx_assert(&sc->sc_lock, SX_LOCKED);

	if (sc->sc_type != G_MIRROR_TYPE_AUTOMATIC)
		return;
	if ((sc->sc_flags & G_MIRROR_DEVICE_FLAG_WIPE) == 0)
		g_mirror_fill_metadata(sc, disk, &md);
	error = g_mirror_write_metadata(disk, &md);
	if (error == 0) {
		G_MIRROR_DEBUG(2, "Metadata on %s updated.",
		    g_mirror_get_diskname(disk));
	} else {
		G_MIRROR_DEBUG(0,
		    "Cannot update metadata on disk %s (error=%d).",
		    g_mirror_get_diskname(disk), error);
	}
}