#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  val ;
struct g_concat_softc {int sc_ndisks; struct g_concat_disk* sc_disks; } ;
struct g_concat_disk {scalar_t__ d_candelete; int /*<<< orphan*/  d_removed; } ;
struct bio {TYPE_2__* bio_to; } ;
struct TYPE_4__ {TYPE_1__* geom; } ;
struct TYPE_3__ {struct g_concat_softc* softc; } ;

/* Variables and functions */
 int /*<<< orphan*/  g_handleattr (struct bio*,char*,int*,int) ; 

__attribute__((used)) static void
g_concat_candelete(struct bio *bp)
{
	struct g_concat_softc *sc;
	struct g_concat_disk *disk;
	int i, val;

	sc = bp->bio_to->geom->softc;
	for (i = 0; i < sc->sc_ndisks; i++) {
		disk = &sc->sc_disks[i];
		if (!disk->d_removed && disk->d_candelete)
			break;
	}
	val = i < sc->sc_ndisks;
	g_handleattr(bp, "GEOM::candelete", &val, sizeof(val));
}