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
struct g_raid3_disk {TYPE_1__* d_softc; } ;
struct TYPE_2__ {int /*<<< orphan*/  sc_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  G_RAID3_DEBUG (int,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  SX_LOCKED ; 
 int /*<<< orphan*/  g_raid3_get_diskname (struct g_raid3_disk*) ; 
 int g_raid3_write_metadata (struct g_raid3_disk*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_topology_assert_not () ; 
 int /*<<< orphan*/  sx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int
g_raid3_clear_metadata(struct g_raid3_disk *disk)
{
	int error;

	g_topology_assert_not();
	sx_assert(&disk->d_softc->sc_lock, SX_LOCKED);

	error = g_raid3_write_metadata(disk, NULL);
	if (error == 0) {
		G_RAID3_DEBUG(2, "Metadata on %s cleared.",
		    g_raid3_get_diskname(disk));
	} else {
		G_RAID3_DEBUG(0,
		    "Cannot clear metadata on disk %s (error=%d).",
		    g_raid3_get_diskname(disk), error);
	}
	return (error);
}