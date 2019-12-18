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
struct g_raid_tr_object {TYPE_1__* tro_volume; } ;
struct g_raid_subdisk {int dummy; } ;
struct bio {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  v_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 struct bio* g_clone_bio (struct bio*) ; 
 int /*<<< orphan*/  g_raid_iodone (struct bio*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_raid_subdisk_iostart (struct g_raid_subdisk*,struct bio*) ; 
 struct g_raid_subdisk* g_raid_tr_raid1_select_read_disk (TYPE_1__*,struct bio*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
g_raid_tr_iostart_raid1_read(struct g_raid_tr_object *tr, struct bio *bp)
{
	struct g_raid_subdisk *sd;
	struct bio *cbp;

	sd = g_raid_tr_raid1_select_read_disk(tr->tro_volume, bp, 0);
	KASSERT(sd != NULL, ("No active disks in volume %s.",
		tr->tro_volume->v_name));

	cbp = g_clone_bio(bp);
	if (cbp == NULL) {
		g_raid_iodone(bp, ENOMEM);
		return;
	}

	g_raid_subdisk_iostart(sd, cbp);
}