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
struct g_mirror_disk {TYPE_1__* d_softc; } ;
struct TYPE_2__ {scalar_t__ sc_type; int /*<<< orphan*/  sc_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  G_MIRROR_DEBUG (int,char*,int /*<<< orphan*/ ,...) ; 
 scalar_t__ G_MIRROR_TYPE_AUTOMATIC ; 
 int /*<<< orphan*/  SX_LOCKED ; 
 int /*<<< orphan*/  g_mirror_get_diskname (struct g_mirror_disk*) ; 
 int g_mirror_write_metadata (struct g_mirror_disk*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_topology_assert_not () ; 
 int /*<<< orphan*/  sx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
g_mirror_clear_metadata(struct g_mirror_disk *disk)
{
	int error;

	g_topology_assert_not();
	sx_assert(&disk->d_softc->sc_lock, SX_LOCKED);

	if (disk->d_softc->sc_type != G_MIRROR_TYPE_AUTOMATIC)
		return (0);
	error = g_mirror_write_metadata(disk, NULL);
	if (error == 0) {
		G_MIRROR_DEBUG(2, "Metadata on %s cleared.",
		    g_mirror_get_diskname(disk));
	} else {
		G_MIRROR_DEBUG(0,
		    "Cannot clear metadata on disk %s (error=%d).",
		    g_mirror_get_diskname(disk), error);
	}
	return (error);
}