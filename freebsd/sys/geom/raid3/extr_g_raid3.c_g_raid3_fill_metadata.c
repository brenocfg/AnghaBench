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
struct g_raid3_softc {int sc_ndisks; int sc_flags; int /*<<< orphan*/  sc_sectorsize; int /*<<< orphan*/  sc_mediasize; int /*<<< orphan*/  sc_genid; int /*<<< orphan*/  sc_id; int /*<<< orphan*/  sc_name; } ;
struct g_raid3_metadata {int md_all; int md_mflags; int md_dflags; int md_sync_offset; int /*<<< orphan*/  md_provsize; int /*<<< orphan*/  md_provider; int /*<<< orphan*/  md_syncid; int /*<<< orphan*/  md_no; int /*<<< orphan*/  md_sectorsize; int /*<<< orphan*/  md_mediasize; int /*<<< orphan*/  md_genid; int /*<<< orphan*/  md_id; int /*<<< orphan*/  md_name; int /*<<< orphan*/  md_version; int /*<<< orphan*/  md_magic; } ;
struct TYPE_3__ {int ds_offset_done; int /*<<< orphan*/  ds_syncid; } ;
struct g_raid3_disk {int d_flags; scalar_t__ d_state; TYPE_2__* d_consumer; TYPE_1__ d_sync; int /*<<< orphan*/  d_no; struct g_raid3_softc* d_softc; } ;
struct g_provider {int /*<<< orphan*/  mediasize; int /*<<< orphan*/  name; } ;
struct TYPE_4__ {struct g_provider* provider; } ;

/* Variables and functions */
 int G_RAID3_DEVICE_FLAG_MASK ; 
 int G_RAID3_DISK_FLAG_HARDCODED ; 
 int G_RAID3_DISK_FLAG_MASK ; 
 scalar_t__ G_RAID3_DISK_STATE_SYNCHRONIZING ; 
 int /*<<< orphan*/  G_RAID3_MAGIC ; 
 int /*<<< orphan*/  G_RAID3_VERSION ; 
 int /*<<< orphan*/  bzero (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void
g_raid3_fill_metadata(struct g_raid3_disk *disk, struct g_raid3_metadata *md)
{
	struct g_raid3_softc *sc;
	struct g_provider *pp;

	sc = disk->d_softc;
	strlcpy(md->md_magic, G_RAID3_MAGIC, sizeof(md->md_magic));
	md->md_version = G_RAID3_VERSION;
	strlcpy(md->md_name, sc->sc_name, sizeof(md->md_name));
	md->md_id = sc->sc_id;
	md->md_all = sc->sc_ndisks;
	md->md_genid = sc->sc_genid;
	md->md_mediasize = sc->sc_mediasize;
	md->md_sectorsize = sc->sc_sectorsize;
	md->md_mflags = (sc->sc_flags & G_RAID3_DEVICE_FLAG_MASK);
	md->md_no = disk->d_no;
	md->md_syncid = disk->d_sync.ds_syncid;
	md->md_dflags = (disk->d_flags & G_RAID3_DISK_FLAG_MASK);
	if (disk->d_state != G_RAID3_DISK_STATE_SYNCHRONIZING)
		md->md_sync_offset = 0;
	else {
		md->md_sync_offset =
		    disk->d_sync.ds_offset_done / (sc->sc_ndisks - 1);
	}
	if (disk->d_consumer != NULL && disk->d_consumer->provider != NULL)
		pp = disk->d_consumer->provider;
	else
		pp = NULL;
	if ((disk->d_flags & G_RAID3_DISK_FLAG_HARDCODED) != 0 && pp != NULL)
		strlcpy(md->md_provider, pp->name, sizeof(md->md_provider));
	else
		bzero(md->md_provider, sizeof(md->md_provider));
	if (pp != NULL)
		md->md_provsize = pp->mediasize;
	else
		md->md_provsize = 0;
}