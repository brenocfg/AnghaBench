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
struct g_raid_tr_object {int /*<<< orphan*/  tro_volume; } ;
struct g_raid_subdisk {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  g_raid_tr_update_state_raid5 (int /*<<< orphan*/ ,struct g_raid_subdisk*) ; 

__attribute__((used)) static int
g_raid_tr_event_raid5(struct g_raid_tr_object *tr,
    struct g_raid_subdisk *sd, u_int event)
{

	g_raid_tr_update_state_raid5(tr->tro_volume, sd);
	return (0);
}