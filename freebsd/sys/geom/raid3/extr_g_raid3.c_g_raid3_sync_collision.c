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
struct g_raid3_softc {int sc_ndisks; struct g_raid3_disk* sc_syncdisk; } ;
struct TYPE_2__ {struct bio** ds_bios; } ;
struct g_raid3_disk {TYPE_1__ d_sync; } ;
struct bio {int bio_offset; int bio_length; scalar_t__ bio_cmd; } ;
typedef  int off_t ;

/* Variables and functions */
 scalar_t__ BIO_WRITE ; 
 int g_raid3_syncreqs ; 

__attribute__((used)) static int
g_raid3_sync_collision(struct g_raid3_softc *sc, struct bio *bp)
{
	struct g_raid3_disk *disk;
	struct bio *sbp;
	off_t rstart, rend, sstart, send;
	int i;

	disk = sc->sc_syncdisk;
	if (disk == NULL)
		return (0);
	rstart = bp->bio_offset;
	rend = bp->bio_offset + bp->bio_length;
	for (i = 0; i < g_raid3_syncreqs; i++) {
		sbp = disk->d_sync.ds_bios[i];
		if (sbp == NULL)
			continue;
		sstart = sbp->bio_offset;
		send = sbp->bio_length;
		if (sbp->bio_cmd == BIO_WRITE) {
			sstart *= sc->sc_ndisks - 1;
			send *= sc->sc_ndisks - 1;
		}
		send += sstart;
		if (rend > sstart && rstart < send)
			return (1);
	}
	return (0);
}