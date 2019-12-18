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
typedef  size_t u_int ;
struct g_raid_volume {size_t v_disks_count; struct g_raid_subdisk* v_subdisks; struct g_raid_softc* v_softc; } ;
struct g_raid_subdisk {int sd_state; } ;
struct g_raid_softc {int /*<<< orphan*/  sc_lock; } ;

/* Variables and functions */
 int G_RAID_SUBDISK_S_NONE ; 
 int /*<<< orphan*/  SX_LOCKED ; 
 int /*<<< orphan*/  sx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

u_int
g_raid_nsubdisks(struct g_raid_volume *vol, int state)
{
	struct g_raid_subdisk *subdisk;
	struct g_raid_softc *sc;
	u_int i, n ;

	sc = vol->v_softc;
	sx_assert(&sc->sc_lock, SX_LOCKED);

	n = 0;
	for (i = 0; i < vol->v_disks_count; i++) {
		subdisk = &vol->v_subdisks[i];
		if ((state == -1 &&
		     subdisk->sd_state != G_RAID_SUBDISK_S_NONE) ||
		    subdisk->sd_state == state)
			n++;
	}
	return (n);
}