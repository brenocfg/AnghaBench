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
struct g_raid_volume {int v_disks_count; scalar_t__ v_state; scalar_t__ v_tr; struct g_raid_softc* v_softc; } ;
struct g_raid_tr_raid5_object {int trso_flags; scalar_t__ trso_stopping; scalar_t__ trso_starting; } ;
struct g_raid_subdisk {int dummy; } ;
struct g_raid_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  G_RAID_EVENT_VOLUME ; 
 int /*<<< orphan*/  G_RAID_SUBDISK_S_ACTIVE ; 
 int /*<<< orphan*/  G_RAID_SUBDISK_S_RESYNC ; 
 int /*<<< orphan*/  G_RAID_SUBDISK_S_STALE ; 
 int /*<<< orphan*/  G_RAID_SUBDISK_S_UNINITIALIZED ; 
 int /*<<< orphan*/  G_RAID_VOLUME_E_DOWN ; 
 int /*<<< orphan*/  G_RAID_VOLUME_E_UP ; 
 scalar_t__ G_RAID_VOLUME_S_ALIVE (scalar_t__) ; 
 scalar_t__ G_RAID_VOLUME_S_BROKEN ; 
 scalar_t__ G_RAID_VOLUME_S_DEGRADED ; 
 scalar_t__ G_RAID_VOLUME_S_OPTIMAL ; 
 scalar_t__ G_RAID_VOLUME_S_STARTING ; 
 scalar_t__ G_RAID_VOLUME_S_STOPPED ; 
 scalar_t__ G_RAID_VOLUME_S_SUBOPTIMAL ; 
 int TR_RAID5_F_DOING_SOME ; 
 int /*<<< orphan*/  g_raid_change_volume_state (struct g_raid_volume*,scalar_t__) ; 
 int /*<<< orphan*/  g_raid_event_send (struct g_raid_volume*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int g_raid_nsubdisks (struct g_raid_volume*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_raid_write_metadata (struct g_raid_softc*,struct g_raid_volume*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
g_raid_tr_update_state_raid5(struct g_raid_volume *vol,
    struct g_raid_subdisk *sd)
{
	struct g_raid_tr_raid5_object *trs;
	struct g_raid_softc *sc;
	u_int s;
	int na, ns, nu;

	sc = vol->v_softc;
	trs = (struct g_raid_tr_raid5_object *)vol->v_tr;
	if (trs->trso_stopping &&
	    (trs->trso_flags & TR_RAID5_F_DOING_SOME) == 0)
		s = G_RAID_VOLUME_S_STOPPED;
	else if (trs->trso_starting)
		s = G_RAID_VOLUME_S_STARTING;
	else {
		na = g_raid_nsubdisks(vol, G_RAID_SUBDISK_S_ACTIVE);
		ns = g_raid_nsubdisks(vol, G_RAID_SUBDISK_S_STALE) +
		     g_raid_nsubdisks(vol, G_RAID_SUBDISK_S_RESYNC);
		nu = g_raid_nsubdisks(vol, G_RAID_SUBDISK_S_UNINITIALIZED);
		if (na == vol->v_disks_count)
			s = G_RAID_VOLUME_S_OPTIMAL;
		else if (na + ns == vol->v_disks_count ||
		    na + ns + nu == vol->v_disks_count /* XXX: Temporary. */)
			s = G_RAID_VOLUME_S_SUBOPTIMAL;
		else if (na == vol->v_disks_count - 1 ||
		    na + ns + nu == vol->v_disks_count)
			s = G_RAID_VOLUME_S_DEGRADED;
		else
			s = G_RAID_VOLUME_S_BROKEN;
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