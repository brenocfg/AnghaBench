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
typedef  int u_int ;
struct g_raid_volume {scalar_t__ v_provider_open; scalar_t__ v_stopping; int /*<<< orphan*/ * v_rootmount; scalar_t__ v_starting; int /*<<< orphan*/  v_tr; int /*<<< orphan*/ * v_provider; int /*<<< orphan*/  v_name; struct g_raid_softc* v_softc; } ;
struct g_raid_softc {int /*<<< orphan*/  sc_md; int /*<<< orphan*/  sc_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  G_RAID_DEBUG1 (int,struct g_raid_softc*,char*,int /*<<< orphan*/ *,...) ; 
 int /*<<< orphan*/  G_RAID_MD_VOLUME_EVENT (int /*<<< orphan*/ ,struct g_raid_volume*,int) ; 
 int /*<<< orphan*/  G_RAID_TR_START (int /*<<< orphan*/ ) ; 
#define  G_RAID_VOLUME_E_DOWN 130 
#define  G_RAID_VOLUME_E_START 129 
#define  G_RAID_VOLUME_E_UP 128 
 int /*<<< orphan*/  SX_XLOCKED ; 
 int /*<<< orphan*/  g_raid_destroy_provider (struct g_raid_volume*) ; 
 int /*<<< orphan*/  g_raid_destroy_volume (struct g_raid_volume*) ; 
 int /*<<< orphan*/  g_raid_launch_provider (struct g_raid_volume*) ; 
 int /*<<< orphan*/  g_raid_volume_event2str (int) ; 
 int /*<<< orphan*/  root_mount_rel (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
g_raid_update_volume(struct g_raid_volume *vol, u_int event)
{
	struct g_raid_softc *sc;

	sc = vol->v_softc;
	sx_assert(&sc->sc_lock, SX_XLOCKED);

	G_RAID_DEBUG1(2, sc, "Event %s for volume %s.",
	    g_raid_volume_event2str(event),
	    vol->v_name);
	switch (event) {
	case G_RAID_VOLUME_E_DOWN:
		if (vol->v_provider != NULL)
			g_raid_destroy_provider(vol);
		break;
	case G_RAID_VOLUME_E_UP:
		if (vol->v_provider == NULL)
			g_raid_launch_provider(vol);
		break;
	case G_RAID_VOLUME_E_START:
		if (vol->v_tr)
			G_RAID_TR_START(vol->v_tr);
		return (0);
	default:
		if (sc->sc_md)
			G_RAID_MD_VOLUME_EVENT(sc->sc_md, vol, event);
		return (0);
	}

	/* Manage root mount release. */
	if (vol->v_starting) {
		vol->v_starting = 0;
		G_RAID_DEBUG1(1, sc, "root_mount_rel %p", vol->v_rootmount);
		root_mount_rel(vol->v_rootmount);
		vol->v_rootmount = NULL;
	}
	if (vol->v_stopping && vol->v_provider_open == 0)
		g_raid_destroy_volume(vol);
	return (0);
}