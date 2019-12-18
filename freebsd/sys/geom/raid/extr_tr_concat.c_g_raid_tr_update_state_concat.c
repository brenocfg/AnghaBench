#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u_int ;
struct g_raid_volume {int v_disks_count; scalar_t__ v_state; scalar_t__ v_raid_level; scalar_t__ v_mediasize; TYPE_1__* v_subdisks; scalar_t__ v_tr; struct g_raid_softc* v_softc; } ;
struct g_raid_tr_concat_object {scalar_t__ trso_stopped; scalar_t__ trso_starting; } ;
struct g_raid_softc {int dummy; } ;
typedef  scalar_t__ off_t ;
struct TYPE_2__ {scalar_t__ sd_state; scalar_t__ sd_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  G_RAID_EVENT_VOLUME ; 
 int /*<<< orphan*/  G_RAID_SUBDISK_S_ACTIVE ; 
 int /*<<< orphan*/  G_RAID_SUBDISK_S_FAILED ; 
 scalar_t__ G_RAID_SUBDISK_S_NONE ; 
 int /*<<< orphan*/  G_RAID_VOLUME_E_DOWN ; 
 int /*<<< orphan*/  G_RAID_VOLUME_E_UP ; 
 scalar_t__ G_RAID_VOLUME_RL_CONCAT ; 
 scalar_t__ G_RAID_VOLUME_S_ALIVE (scalar_t__) ; 
 scalar_t__ G_RAID_VOLUME_S_BROKEN ; 
 scalar_t__ G_RAID_VOLUME_S_OPTIMAL ; 
 scalar_t__ G_RAID_VOLUME_S_STARTING ; 
 scalar_t__ G_RAID_VOLUME_S_STOPPED ; 
 scalar_t__ G_RAID_VOLUME_S_SUBOPTIMAL ; 
 int /*<<< orphan*/  g_raid_change_volume_state (struct g_raid_volume*,scalar_t__) ; 
 int /*<<< orphan*/  g_raid_event_send (struct g_raid_volume*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int g_raid_nsubdisks (struct g_raid_volume*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_raid_write_metadata (struct g_raid_softc*,struct g_raid_volume*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
g_raid_tr_update_state_concat(struct g_raid_volume *vol)
{
	struct g_raid_tr_concat_object *trs;
	struct g_raid_softc *sc;
	off_t size;
	u_int s;
	int i, n, f;

	sc = vol->v_softc;
	trs = (struct g_raid_tr_concat_object *)vol->v_tr;
	if (trs->trso_stopped)
		s = G_RAID_VOLUME_S_STOPPED;
	else if (trs->trso_starting)
		s = G_RAID_VOLUME_S_STARTING;
	else {
		n = g_raid_nsubdisks(vol, G_RAID_SUBDISK_S_ACTIVE);
		f = g_raid_nsubdisks(vol, G_RAID_SUBDISK_S_FAILED);
		if (n + f == vol->v_disks_count) {
			if (f == 0)
				s = G_RAID_VOLUME_S_OPTIMAL;
			else
				s = G_RAID_VOLUME_S_SUBOPTIMAL;
		} else
			s = G_RAID_VOLUME_S_BROKEN;
	}
	if (s != vol->v_state) {

		/*
		 * Some metadata modules may not know CONCAT volume
		 * mediasize until all disks connected. Recalculate.
		 */
		if (vol->v_raid_level == G_RAID_VOLUME_RL_CONCAT &&
		    G_RAID_VOLUME_S_ALIVE(s) &&
		    !G_RAID_VOLUME_S_ALIVE(vol->v_state)) {
			size = 0;
			for (i = 0; i < vol->v_disks_count; i++) {
				if (vol->v_subdisks[i].sd_state !=
				    G_RAID_SUBDISK_S_NONE)
					size += vol->v_subdisks[i].sd_size;
			}
			vol->v_mediasize = size;
		}

		g_raid_event_send(vol, G_RAID_VOLUME_S_ALIVE(s) ?
		    G_RAID_VOLUME_E_UP : G_RAID_VOLUME_E_DOWN,
		    G_RAID_EVENT_VOLUME);
		g_raid_change_volume_state(vol, s);
		if (!trs->trso_starting && !trs->trso_stopped)
			g_raid_write_metadata(sc, vol, NULL, NULL);
	}
	return (0);
}