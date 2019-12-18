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
typedef  scalar_t__ u_int ;
struct g_raid_volume {int v_disks_count; scalar_t__ v_state; scalar_t__ v_tr; int /*<<< orphan*/  v_name; struct g_raid_subdisk* v_subdisks; struct g_raid_softc* v_softc; } ;
struct g_raid_tr_raid1_object {int trso_flags; scalar_t__ trso_stopping; scalar_t__ trso_starting; } ;
struct g_raid_subdisk {scalar_t__ sd_state; scalar_t__ sd_rebuild_pos; int /*<<< orphan*/ * sd_disk; int /*<<< orphan*/  sd_pos; } ;
struct g_raid_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  G_RAID_DEBUG1 (int,struct g_raid_softc*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  G_RAID_EVENT_VOLUME ; 
 scalar_t__ G_RAID_SUBDISK_S_ACTIVE ; 
 scalar_t__ G_RAID_SUBDISK_S_REBUILD ; 
 scalar_t__ G_RAID_SUBDISK_S_RESYNC ; 
 scalar_t__ G_RAID_SUBDISK_S_STALE ; 
 scalar_t__ G_RAID_SUBDISK_S_UNINITIALIZED ; 
 int /*<<< orphan*/  G_RAID_VOLUME_E_DOWN ; 
 int /*<<< orphan*/  G_RAID_VOLUME_E_UP ; 
 scalar_t__ G_RAID_VOLUME_S_ALIVE (scalar_t__) ; 
 scalar_t__ G_RAID_VOLUME_S_BROKEN ; 
 scalar_t__ G_RAID_VOLUME_S_DEGRADED ; 
 scalar_t__ G_RAID_VOLUME_S_OPTIMAL ; 
 scalar_t__ G_RAID_VOLUME_S_STARTING ; 
 scalar_t__ G_RAID_VOLUME_S_STOPPED ; 
 scalar_t__ G_RAID_VOLUME_S_SUBOPTIMAL ; 
 int TR_RAID1_F_DOING_SOME ; 
 int /*<<< orphan*/  g_raid_change_subdisk_state (struct g_raid_subdisk*,scalar_t__) ; 
 int /*<<< orphan*/  g_raid_change_volume_state (struct g_raid_volume*,scalar_t__) ; 
 int /*<<< orphan*/  g_raid_event_send (struct g_raid_volume*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int g_raid_nsubdisks (struct g_raid_volume*,scalar_t__) ; 
 int /*<<< orphan*/  g_raid_subdisk_state2str (scalar_t__) ; 
 int /*<<< orphan*/  g_raid_tr_raid1_maybe_rebuild (scalar_t__,struct g_raid_subdisk*) ; 
 int /*<<< orphan*/  g_raid_write_metadata (struct g_raid_softc*,struct g_raid_volume*,struct g_raid_subdisk*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
g_raid_tr_update_state_raid1(struct g_raid_volume *vol,
    struct g_raid_subdisk *sd)
{
	struct g_raid_tr_raid1_object *trs;
	struct g_raid_softc *sc;
	struct g_raid_subdisk *tsd, *bestsd;
	u_int s;
	int i, na, ns;

	sc = vol->v_softc;
	trs = (struct g_raid_tr_raid1_object *)vol->v_tr;
	if (trs->trso_stopping &&
	    (trs->trso_flags & TR_RAID1_F_DOING_SOME) == 0)
		s = G_RAID_VOLUME_S_STOPPED;
	else if (trs->trso_starting)
		s = G_RAID_VOLUME_S_STARTING;
	else {
		/* Make sure we have at least one ACTIVE disk. */
		na = g_raid_nsubdisks(vol, G_RAID_SUBDISK_S_ACTIVE);
		if (na == 0) {
			/*
			 * Critical situation! We have no any active disk!
			 * Choose the best disk we have to make it active.
			 */
			bestsd = &vol->v_subdisks[0];
			for (i = 1; i < vol->v_disks_count; i++) {
				tsd = &vol->v_subdisks[i];
				if (tsd->sd_state > bestsd->sd_state)
					bestsd = tsd;
				else if (tsd->sd_state == bestsd->sd_state &&
				    (tsd->sd_state == G_RAID_SUBDISK_S_REBUILD ||
				     tsd->sd_state == G_RAID_SUBDISK_S_RESYNC) &&
				    tsd->sd_rebuild_pos > bestsd->sd_rebuild_pos)
					bestsd = tsd;
			}
			if (bestsd->sd_state >= G_RAID_SUBDISK_S_UNINITIALIZED) {
				/* We found reasonable candidate. */
				G_RAID_DEBUG1(1, sc,
				    "Promote subdisk %s:%d from %s to ACTIVE.",
				    vol->v_name, bestsd->sd_pos,
				    g_raid_subdisk_state2str(bestsd->sd_state));
				g_raid_change_subdisk_state(bestsd,
				    G_RAID_SUBDISK_S_ACTIVE);
				g_raid_write_metadata(sc,
				    vol, bestsd, bestsd->sd_disk);
			}
		}
		na = g_raid_nsubdisks(vol, G_RAID_SUBDISK_S_ACTIVE);
		ns = g_raid_nsubdisks(vol, G_RAID_SUBDISK_S_STALE) +
		     g_raid_nsubdisks(vol, G_RAID_SUBDISK_S_RESYNC);
		if (na == vol->v_disks_count)
			s = G_RAID_VOLUME_S_OPTIMAL;
		else if (na + ns == vol->v_disks_count)
			s = G_RAID_VOLUME_S_SUBOPTIMAL;
		else if (na > 0)
			s = G_RAID_VOLUME_S_DEGRADED;
		else
			s = G_RAID_VOLUME_S_BROKEN;
		g_raid_tr_raid1_maybe_rebuild(vol->v_tr, sd);
	}
	if (s != vol->v_state) {
		g_raid_event_send(vol, G_RAID_VOLUME_S_ALIVE(s) ?
		    G_RAID_VOLUME_E_UP : G_RAID_VOLUME_E_DOWN,
		    G_RAID_EVENT_VOLUME);
		g_raid_change_volume_state(vol, s);
		if (!trs->trso_starting && !trs->trso_stopping)
			g_raid_write_metadata(sc, vol, NULL, NULL);
	}
	return (0);
}