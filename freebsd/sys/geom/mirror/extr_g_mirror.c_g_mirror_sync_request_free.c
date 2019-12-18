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
struct TYPE_2__ {struct bio** ds_bios; } ;
struct g_mirror_disk {TYPE_1__ d_sync; } ;
struct bio {int /*<<< orphan*/  bio_data; scalar_t__ bio_caller1; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  M_MIRROR ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_destroy_bio (struct bio*) ; 

__attribute__((used)) static void
g_mirror_sync_request_free(struct g_mirror_disk *disk, struct bio *bp)
{
	int idx;

	if (disk != NULL && disk->d_sync.ds_bios != NULL) {
		idx = (int)(uintptr_t)bp->bio_caller1;
		KASSERT(disk->d_sync.ds_bios[idx] == bp,
		    ("unexpected sync BIO at %p:%d", disk, idx));
		disk->d_sync.ds_bios[idx] = NULL;
	}
	free(bp->bio_data, M_MIRROR);
	g_destroy_bio(bp);
}