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
struct g_provider {int dummy; } ;
struct g_mirror_softc {int dummy; } ;
struct g_mirror_metadata {char* md_provider; int /*<<< orphan*/  md_mediasize; int /*<<< orphan*/  md_balance; int /*<<< orphan*/  md_slice; int /*<<< orphan*/  md_all; int /*<<< orphan*/  md_syncid; int /*<<< orphan*/  md_genid; int /*<<< orphan*/  md_sync_offset; int /*<<< orphan*/  md_dflags; int /*<<< orphan*/  md_priority; int /*<<< orphan*/  md_did; } ;
struct TYPE_2__ {int /*<<< orphan*/  ds_syncid; int /*<<< orphan*/  ds_update_ts; int /*<<< orphan*/  ds_offset_done; int /*<<< orphan*/  ds_offset; int /*<<< orphan*/ * ds_consumer; } ;
struct g_mirror_disk {int /*<<< orphan*/  d_init_mediasize; int /*<<< orphan*/  d_init_balance; int /*<<< orphan*/  d_init_slice; int /*<<< orphan*/  d_init_ndisks; TYPE_1__ d_sync; int /*<<< orphan*/  d_genid; int /*<<< orphan*/  d_flags; int /*<<< orphan*/  d_consumer; int /*<<< orphan*/  d_priority; int /*<<< orphan*/  d_state; int /*<<< orphan*/  d_id; struct g_mirror_softc* d_softc; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  G_MIRROR_DISK_FLAG_CANDELETE ; 
 int /*<<< orphan*/  G_MIRROR_DISK_FLAG_HARDCODED ; 
 int /*<<< orphan*/  G_MIRROR_DISK_STATE_NONE ; 
 int /*<<< orphan*/  M_MIRROR ; 
 int M_NOWAIT ; 
 int M_ZERO ; 
 int /*<<< orphan*/  free (struct g_mirror_disk*,int /*<<< orphan*/ ) ; 
 int g_getattr (char*,int /*<<< orphan*/ ,int*) ; 
 int g_mirror_connect_disk (struct g_mirror_disk*,struct g_provider*) ; 
 struct g_mirror_disk* malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  time_uptime ; 

__attribute__((used)) static struct g_mirror_disk *
g_mirror_init_disk(struct g_mirror_softc *sc, struct g_provider *pp,
    struct g_mirror_metadata *md, int *errorp)
{
	struct g_mirror_disk *disk;
	int i, error;

	disk = malloc(sizeof(*disk), M_MIRROR, M_NOWAIT | M_ZERO);
	if (disk == NULL) {
		error = ENOMEM;
		goto fail;
	}
	disk->d_softc = sc;
	error = g_mirror_connect_disk(disk, pp);
	if (error != 0)
		goto fail;
	disk->d_id = md->md_did;
	disk->d_state = G_MIRROR_DISK_STATE_NONE;
	disk->d_priority = md->md_priority;
	disk->d_flags = md->md_dflags;
	error = g_getattr("GEOM::candelete", disk->d_consumer, &i);
	if (error == 0 && i != 0)
		disk->d_flags |= G_MIRROR_DISK_FLAG_CANDELETE;
	if (md->md_provider[0] != '\0')
		disk->d_flags |= G_MIRROR_DISK_FLAG_HARDCODED;
	disk->d_sync.ds_consumer = NULL;
	disk->d_sync.ds_offset = md->md_sync_offset;
	disk->d_sync.ds_offset_done = md->md_sync_offset;
	disk->d_sync.ds_update_ts = time_uptime;
	disk->d_genid = md->md_genid;
	disk->d_sync.ds_syncid = md->md_syncid;
	disk->d_init_ndisks = md->md_all;
	disk->d_init_slice = md->md_slice;
	disk->d_init_balance = md->md_balance;
	disk->d_init_mediasize = md->md_mediasize;
	if (errorp != NULL)
		*errorp = 0;
	return (disk);
fail:
	if (errorp != NULL)
		*errorp = error;
	if (disk != NULL)
		free(disk, M_MIRROR);
	return (NULL);
}