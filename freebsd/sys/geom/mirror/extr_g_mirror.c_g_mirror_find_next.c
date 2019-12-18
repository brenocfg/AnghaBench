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
struct g_mirror_softc {int /*<<< orphan*/  sc_disks; } ;
struct g_mirror_disk {scalar_t__ d_state; } ;

/* Variables and functions */
 scalar_t__ G_MIRROR_DISK_STATE_ACTIVE ; 
 struct g_mirror_disk* LIST_FIRST (int /*<<< orphan*/ *) ; 
 struct g_mirror_disk* LIST_NEXT (struct g_mirror_disk*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  d_next ; 

__attribute__((used)) static __inline struct g_mirror_disk *
g_mirror_find_next(struct g_mirror_softc *sc, struct g_mirror_disk *disk)
{
	struct g_mirror_disk *dp;

	for (dp = LIST_NEXT(disk, d_next); dp != disk;
	    dp = LIST_NEXT(dp, d_next)) {
		if (dp == NULL)
			dp = LIST_FIRST(&sc->sc_disks);
		if (dp->d_state == G_MIRROR_DISK_STATE_ACTIVE)
			break;
	}
	if (dp->d_state != G_MIRROR_DISK_STATE_ACTIVE)
		return (NULL);
	return (dp);
}