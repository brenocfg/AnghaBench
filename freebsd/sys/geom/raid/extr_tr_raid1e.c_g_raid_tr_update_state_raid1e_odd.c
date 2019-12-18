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
struct g_raid_volume {int v_disks_count; struct g_raid_subdisk* v_subdisks; int /*<<< orphan*/  v_name; struct g_raid_softc* v_softc; } ;
struct g_raid_subdisk {scalar_t__ sd_state; scalar_t__ sd_rebuild_pos; int /*<<< orphan*/  sd_disk; int /*<<< orphan*/  sd_pos; } ;
struct g_raid_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  G_RAID_DEBUG1 (int,struct g_raid_softc*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ G_RAID_SUBDISK_S_ACTIVE ; 
 scalar_t__ G_RAID_SUBDISK_S_REBUILD ; 
 scalar_t__ G_RAID_SUBDISK_S_RESYNC ; 
 scalar_t__ G_RAID_SUBDISK_S_STALE ; 
 scalar_t__ G_RAID_SUBDISK_S_UNINITIALIZED ; 
 int G_RAID_VOLUME_S_BROKEN ; 
 int G_RAID_VOLUME_S_DEGRADED ; 
 int G_RAID_VOLUME_S_OPTIMAL ; 
 int G_RAID_VOLUME_S_SUBOPTIMAL ; 
 int N ; 
 int /*<<< orphan*/  g_raid_change_subdisk_state (struct g_raid_subdisk*,scalar_t__) ; 
 int g_raid_nsubdisks (struct g_raid_volume*,scalar_t__) ; 
 int /*<<< orphan*/  g_raid_subdisk_state2str (scalar_t__) ; 
 int /*<<< orphan*/  g_raid_write_metadata (struct g_raid_softc*,struct g_raid_volume*,struct g_raid_subdisk*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
g_raid_tr_update_state_raid1e_odd(struct g_raid_volume *vol)
{
	struct g_raid_softc *sc;
	struct g_raid_subdisk *sd, *bestsd, *worstsd;
	int i, j, state, sstate;

	sc = vol->v_softc;
	if (g_raid_nsubdisks(vol, G_RAID_SUBDISK_S_ACTIVE) ==
	    vol->v_disks_count)
		return (G_RAID_VOLUME_S_OPTIMAL);
	for (i = 0; i < vol->v_disks_count; i++) {
		sd = &vol->v_subdisks[i];
		if (sd->sd_state == G_RAID_SUBDISK_S_UNINITIALIZED) {
			/* We found reasonable candidate. */
			G_RAID_DEBUG1(1, sc,
			    "Promote subdisk %s:%d from %s to STALE.",
			    vol->v_name, sd->sd_pos,
			    g_raid_subdisk_state2str(sd->sd_state));
			g_raid_change_subdisk_state(sd,
			    G_RAID_SUBDISK_S_STALE);
			g_raid_write_metadata(sc, vol, sd, sd->sd_disk);
		}
	}
	state = G_RAID_VOLUME_S_OPTIMAL;
	for (i = 0; i < vol->v_disks_count; i++) {
		bestsd = &vol->v_subdisks[i];
		worstsd = &vol->v_subdisks[i];
		for (j = 1; j < N; j++) {
			sd = &vol->v_subdisks[(i + j) % vol->v_disks_count];
			if (sd->sd_state > bestsd->sd_state)
				bestsd = sd;
			else if (sd->sd_state == bestsd->sd_state &&
			    (sd->sd_state == G_RAID_SUBDISK_S_REBUILD ||
			     sd->sd_state == G_RAID_SUBDISK_S_RESYNC) &&
			    sd->sd_rebuild_pos > bestsd->sd_rebuild_pos)
				bestsd = sd;
			if (sd->sd_state < worstsd->sd_state)
				worstsd = sd;
		}
		if (worstsd->sd_state == G_RAID_SUBDISK_S_ACTIVE)
			sstate = G_RAID_VOLUME_S_OPTIMAL;
		else if (worstsd->sd_state >= G_RAID_SUBDISK_S_STALE)
			sstate = G_RAID_VOLUME_S_SUBOPTIMAL;
		else if (bestsd->sd_state >= G_RAID_SUBDISK_S_STALE)
			sstate = G_RAID_VOLUME_S_DEGRADED;
		else
			sstate = G_RAID_VOLUME_S_BROKEN;
		if (sstate < state)
			state = sstate;
	}
	return (state);
}