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
struct g_raid_tr_object {int dummy; } ;
struct g_raid_subdisk {int dummy; } ;
struct bio {scalar_t__ bio_caller1; } ;

/* Variables and functions */
 int /*<<< orphan*/  g_raid_subdisk_iostart (struct g_raid_subdisk*,struct bio*) ; 

__attribute__((used)) static int
g_raid_tr_locked_raid5(struct g_raid_tr_object *tr, void *argp)
{
	struct bio *bp;
	struct g_raid_subdisk *sd;

	bp = (struct bio *)argp;
	sd = (struct g_raid_subdisk *)bp->bio_caller1;
	g_raid_subdisk_iostart(sd, bp);

	return (0);
}