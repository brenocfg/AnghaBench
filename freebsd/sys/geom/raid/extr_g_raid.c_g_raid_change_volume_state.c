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
struct g_raid_volume {int v_state; int /*<<< orphan*/  v_name; int /*<<< orphan*/  v_softc; } ;

/* Variables and functions */
 int /*<<< orphan*/  G_RAID_DEBUG1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_raid_volume_state2str (int) ; 

void
g_raid_change_volume_state(struct g_raid_volume *vol, int state)
{

	G_RAID_DEBUG1(0, vol->v_softc,
	    "Volume %s state changed from %s to %s.",
	    vol->v_name,
	    g_raid_volume_state2str(vol->v_state),
	    g_raid_volume_state2str(state));
	vol->v_state = state;
}