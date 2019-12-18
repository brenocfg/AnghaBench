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
struct g_raid3_softc {struct g_raid3_disk* sc_disks; } ;
struct g_raid3_metadata {size_t md_no; char* md_provider; int /*<<< orphan*/  md_syncid; int /*<<< orphan*/  md_genid; int /*<<< orphan*/  md_sync_offset; int /*<<< orphan*/  md_dflags; } ;
struct TYPE_2__ {int /*<<< orphan*/  ds_syncid; int /*<<< orphan*/  ds_offset_done; int /*<<< orphan*/  ds_offset; int /*<<< orphan*/ * ds_consumer; } ;
struct g_raid3_disk {TYPE_1__ d_sync; int /*<<< orphan*/  d_genid; int /*<<< orphan*/  d_flags; int /*<<< orphan*/  d_state; } ;
struct g_provider {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  G_RAID3_DISK_FLAG_HARDCODED ; 
 int /*<<< orphan*/  G_RAID3_DISK_STATE_NONE ; 
 int g_raid3_connect_disk (struct g_raid3_disk*,struct g_provider*) ; 

__attribute__((used)) static struct g_raid3_disk *
g_raid3_init_disk(struct g_raid3_softc *sc, struct g_provider *pp,
    struct g_raid3_metadata *md, int *errorp)
{
	struct g_raid3_disk *disk;
	int error;

	disk = &sc->sc_disks[md->md_no];
	error = g_raid3_connect_disk(disk, pp);
	if (error != 0) {
		if (errorp != NULL)
			*errorp = error;
		return (NULL);
	}
	disk->d_state = G_RAID3_DISK_STATE_NONE;
	disk->d_flags = md->md_dflags;
	if (md->md_provider[0] != '\0')
		disk->d_flags |= G_RAID3_DISK_FLAG_HARDCODED;
	disk->d_sync.ds_consumer = NULL;
	disk->d_sync.ds_offset = md->md_sync_offset;
	disk->d_sync.ds_offset_done = md->md_sync_offset;
	disk->d_genid = md->md_genid;
	disk->d_sync.ds_syncid = md->md_syncid;
	if (errorp != NULL)
		*errorp = 0;
	return (disk);
}