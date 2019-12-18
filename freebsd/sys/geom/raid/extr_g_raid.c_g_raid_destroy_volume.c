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
struct g_raid_volume {int v_stopping; scalar_t__ v_state; scalar_t__ v_provider_open; int /*<<< orphan*/  v_name; struct g_raid_volume* v_subdisks; struct g_raid_disk* sd_disk; scalar_t__ v_rootmount; int /*<<< orphan*/ * v_tr; int /*<<< orphan*/ * v_provider; struct g_raid_softc* v_softc; } ;
struct g_raid_softc {scalar_t__ sc_stopping; scalar_t__ sc_md; int /*<<< orphan*/  sc_volumes; } ;
struct g_raid_disk {int /*<<< orphan*/  d_subdisks; } ;
typedef  int /*<<< orphan*/  kobj_t ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  G_RAID_DEBUG1 (int,struct g_raid_softc*,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ G_RAID_DESTROY_HARD ; 
 int G_RAID_MAX_SUBDISKS ; 
 int /*<<< orphan*/  G_RAID_MD_FREE_VOLUME (scalar_t__,struct g_raid_volume*) ; 
 int /*<<< orphan*/  G_RAID_NODE_E_WAKE ; 
 int /*<<< orphan*/  G_RAID_TR_FREE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  G_RAID_TR_STOP (int /*<<< orphan*/ *) ; 
 scalar_t__ G_RAID_VOLUME_S_STOPPED ; 
 int /*<<< orphan*/  LIST_REMOVE (struct g_raid_volume*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M_RAID ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct g_raid_volume*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct g_raid_volume*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_raid_event_cancel (struct g_raid_softc*,struct g_raid_volume*) ; 
 scalar_t__ g_raid_event_check (struct g_raid_softc*,struct g_raid_volume*) ; 
 int /*<<< orphan*/  g_raid_event_send (struct g_raid_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_topology_lock () ; 
 int /*<<< orphan*/  g_topology_unlock () ; 
 int /*<<< orphan*/  kobj_delete (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  root_mount_rel (scalar_t__) ; 
 int /*<<< orphan*/  sd_next ; 
 int /*<<< orphan*/  v_global_next ; 
 int /*<<< orphan*/  v_next ; 

int
g_raid_destroy_volume(struct g_raid_volume *vol)
{
	struct g_raid_softc *sc;
	struct g_raid_disk *disk;
	int i;

	sc = vol->v_softc;
	G_RAID_DEBUG1(2, sc, "Destroying volume %s.", vol->v_name);
	vol->v_stopping = 1;
	if (vol->v_state != G_RAID_VOLUME_S_STOPPED) {
		if (vol->v_tr) {
			G_RAID_TR_STOP(vol->v_tr);
			return (EBUSY);
		} else
			vol->v_state = G_RAID_VOLUME_S_STOPPED;
	}
	if (g_raid_event_check(sc, vol) != 0)
		return (EBUSY);
	if (vol->v_provider != NULL)
		return (EBUSY);
	if (vol->v_provider_open != 0)
		return (EBUSY);
	if (vol->v_tr) {
		G_RAID_TR_FREE(vol->v_tr);
		kobj_delete((kobj_t)vol->v_tr, M_RAID);
		vol->v_tr = NULL;
	}
	if (vol->v_rootmount)
		root_mount_rel(vol->v_rootmount);
	g_topology_lock();
	LIST_REMOVE(vol, v_global_next);
	g_topology_unlock();
	TAILQ_REMOVE(&sc->sc_volumes, vol, v_next);
	for (i = 0; i < G_RAID_MAX_SUBDISKS; i++) {
		g_raid_event_cancel(sc, &vol->v_subdisks[i]);
		disk = vol->v_subdisks[i].sd_disk;
		if (disk == NULL)
			continue;
		TAILQ_REMOVE(&disk->d_subdisks, &vol->v_subdisks[i], sd_next);
	}
	G_RAID_DEBUG1(2, sc, "Volume %s destroyed.", vol->v_name);
	if (sc->sc_md)
		G_RAID_MD_FREE_VOLUME(sc->sc_md, vol);
	g_raid_event_cancel(sc, vol);
	free(vol, M_RAID);
	if (sc->sc_stopping == G_RAID_DESTROY_HARD) {
		/* Wake up worker to let it selfdestruct. */
		g_raid_event_send(sc, G_RAID_NODE_E_WAKE, 0);
	}
	return (0);
}