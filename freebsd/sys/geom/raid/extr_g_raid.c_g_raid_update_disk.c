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
typedef  int /*<<< orphan*/  u_int ;
struct g_raid_softc {scalar_t__ sc_md; int /*<<< orphan*/  sc_lock; } ;
struct g_raid_disk {struct g_raid_softc* d_softc; } ;

/* Variables and functions */
 int /*<<< orphan*/  G_RAID_DEBUG1 (int,struct g_raid_softc*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  G_RAID_MD_EVENT (scalar_t__,struct g_raid_disk*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SX_XLOCKED ; 
 int /*<<< orphan*/  g_raid_disk_event2str (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_raid_get_diskname (struct g_raid_disk*) ; 
 int /*<<< orphan*/  sx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
g_raid_update_disk(struct g_raid_disk *disk, u_int event)
{
	struct g_raid_softc *sc;

	sc = disk->d_softc;
	sx_assert(&sc->sc_lock, SX_XLOCKED);

	G_RAID_DEBUG1(2, sc, "Event %s for disk %s.",
	    g_raid_disk_event2str(event),
	    g_raid_get_diskname(disk));

	if (sc->sc_md)
		G_RAID_MD_EVENT(sc->sc_md, disk, event);
	return (0);
}