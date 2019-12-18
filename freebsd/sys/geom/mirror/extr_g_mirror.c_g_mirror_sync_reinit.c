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
struct TYPE_3__ {int /*<<< orphan*/  ds_consumer; } ;
struct g_mirror_disk {TYPE_2__* d_softc; TYPE_1__ d_sync; } ;
struct bio {scalar_t__ bio_offset; int /*<<< orphan*/  bio_length; void* bio_caller1; int /*<<< orphan*/  bio_to; int /*<<< orphan*/  bio_from; int /*<<< orphan*/  bio_done; void* bio_data; int /*<<< orphan*/  bio_cmd; } ;
typedef  scalar_t__ off_t ;
struct TYPE_4__ {scalar_t__ sc_mediasize; int /*<<< orphan*/  sc_provider; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_READ ; 
 int /*<<< orphan*/  MAXPHYS ; 
 int /*<<< orphan*/  MIN (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  g_mirror_sync_done ; 
 int /*<<< orphan*/  g_reset_bio (struct bio*) ; 

__attribute__((used)) static void
g_mirror_sync_reinit(const struct g_mirror_disk *disk, struct bio *bp,
    off_t offset)
{
	void *data;
	int idx;

	data = bp->bio_data;
	idx = (int)(uintptr_t)bp->bio_caller1;
	g_reset_bio(bp);

	bp->bio_cmd = BIO_READ;
	bp->bio_data = data;
	bp->bio_done = g_mirror_sync_done;
	bp->bio_from = disk->d_sync.ds_consumer;
	bp->bio_to = disk->d_softc->sc_provider;
	bp->bio_caller1 = (void *)(uintptr_t)idx;
	bp->bio_offset = offset;
	bp->bio_length = MIN(MAXPHYS,
	    disk->d_softc->sc_mediasize - bp->bio_offset);
}