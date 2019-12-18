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
typedef  int /*<<< orphan*/  vm_offset_t ;
struct g_raid_volume {int /*<<< orphan*/  v_provider; struct g_raid_softc* v_softc; } ;
struct g_raid_tr_object {struct g_raid_volume* tro_volume; } ;
struct g_raid_softc {int dummy; } ;
struct bio {size_t bio_length; int bio_flags; scalar_t__ bio_error; int /*<<< orphan*/  bio_to; void* bio_data; int /*<<< orphan*/  bio_offset; int /*<<< orphan*/ * bio_attribute; int /*<<< orphan*/  bio_done; int /*<<< orphan*/  bio_cmd; } ;
typedef  int /*<<< orphan*/  off_t ;

/* Variables and functions */
 int BIO_DONE ; 
 int /*<<< orphan*/  BIO_WRITE ; 
 int /*<<< orphan*/  DELAY (int) ; 
 int EIO ; 
 int /*<<< orphan*/  G_RAID_DEBUG1 (int,struct g_raid_softc*,char*) ; 
 int /*<<< orphan*/  g_raid_poll (struct g_raid_softc*) ; 
 int /*<<< orphan*/  g_raid_start (struct bio*) ; 
 int /*<<< orphan*/  g_raid_tr_kerneldump_common_done ; 
 int /*<<< orphan*/  g_reset_bio (struct bio*) ; 

int
g_raid_tr_kerneldump_common(struct g_raid_tr_object *tr,
    void *virtual, vm_offset_t physical, off_t offset, size_t length)
{
	struct g_raid_softc *sc;
	struct g_raid_volume *vol;
	struct bio bp;

	vol = tr->tro_volume;
	sc = vol->v_softc;

	g_reset_bio(&bp);
	bp.bio_cmd = BIO_WRITE;
	bp.bio_done = g_raid_tr_kerneldump_common_done;
	bp.bio_attribute = NULL;
	bp.bio_offset = offset;
	bp.bio_length = length;
	bp.bio_data = virtual;
	bp.bio_to = vol->v_provider;

	g_raid_start(&bp);
	while (!(bp.bio_flags & BIO_DONE)) {
		G_RAID_DEBUG1(4, sc, "Poll...");
		g_raid_poll(sc);
		DELAY(10);
	}

	return (bp.bio_error != 0 ? EIO : 0);
}