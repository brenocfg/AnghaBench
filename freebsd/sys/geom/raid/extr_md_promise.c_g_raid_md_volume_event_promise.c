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
struct g_raid_volume {scalar_t__ v_md_data; } ;
struct g_raid_md_promise_pervolume {int /*<<< orphan*/  pv_started; } ;
struct g_raid_md_object {int dummy; } ;

/* Variables and functions */
#define  G_RAID_VOLUME_E_STARTMD 128 
 int /*<<< orphan*/  g_raid_md_promise_start (struct g_raid_volume*) ; 

__attribute__((used)) static int
g_raid_md_volume_event_promise(struct g_raid_md_object *md,
    struct g_raid_volume *vol, u_int event)
{
	struct g_raid_md_promise_pervolume *pv;

	pv = (struct g_raid_md_promise_pervolume *)vol->v_md_data;
	switch (event) {
	case G_RAID_VOLUME_E_STARTMD:
		if (!pv->pv_started)
			g_raid_md_promise_start(vol);
		return (0);
	}
	return (-2);
}