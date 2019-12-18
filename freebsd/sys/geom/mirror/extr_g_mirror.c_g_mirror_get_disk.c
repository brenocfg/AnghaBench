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
struct g_mirror_softc {struct g_mirror_disk* sc_hint; int /*<<< orphan*/  sc_disks; } ;
struct g_mirror_disk {scalar_t__ d_state; } ;

/* Variables and functions */
 scalar_t__ G_MIRROR_DISK_STATE_ACTIVE ; 
 struct g_mirror_disk* LIST_FIRST (int /*<<< orphan*/ *) ; 
 void* g_mirror_find_next (struct g_mirror_softc*,struct g_mirror_disk*) ; 

__attribute__((used)) static struct g_mirror_disk *
g_mirror_get_disk(struct g_mirror_softc *sc)
{
	struct g_mirror_disk *disk;

	if (sc->sc_hint == NULL) {
		sc->sc_hint = LIST_FIRST(&sc->sc_disks);
		if (sc->sc_hint == NULL)
			return (NULL);
	}
	disk = sc->sc_hint;
	if (disk->d_state != G_MIRROR_DISK_STATE_ACTIVE) {
		disk = g_mirror_find_next(sc, disk);
		if (disk == NULL)
			return (NULL);
	}
	sc->sc_hint = g_mirror_find_next(sc, disk);
	return (disk);
}