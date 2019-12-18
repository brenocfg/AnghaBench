#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct nvidia_raid_conf {int total_disks; scalar_t__ disk_number; } ;
struct g_raid_softc {struct g_raid_md_object* sc_md; } ;
struct g_raid_md_object {int dummy; } ;
struct g_raid_md_nvidia_perdisk {struct nvidia_raid_conf* pd_meta; } ;
struct g_raid_md_nvidia_object {int mdio_total_disks; int mdio_disks_present; TYPE_1__* mdio_meta; scalar_t__ mdio_started; } ;
struct g_raid_disk {scalar_t__ d_md_data; struct g_raid_softc* d_softc; } ;
struct TYPE_3__ {scalar_t__ disk_number; scalar_t__ total_disks; } ;

/* Variables and functions */
 int /*<<< orphan*/  G_RAID_DEBUG1 (int,struct g_raid_softc*,char*,...) ; 
 int /*<<< orphan*/  M_MD_NVIDIA ; 
 int /*<<< orphan*/  free (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_raid_md_nvidia_start (struct g_raid_softc*) ; 
 scalar_t__ g_raid_md_nvidia_start_disk (struct g_raid_disk*) ; 
 int /*<<< orphan*/  g_raid_md_write_nvidia (struct g_raid_md_object*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_1__* nvidia_meta_copy (struct nvidia_raid_conf*) ; 

__attribute__((used)) static void
g_raid_md_nvidia_new_disk(struct g_raid_disk *disk)
{
	struct g_raid_softc *sc;
	struct g_raid_md_object *md;
	struct g_raid_md_nvidia_object *mdi;
	struct nvidia_raid_conf *pdmeta;
	struct g_raid_md_nvidia_perdisk *pd;

	sc = disk->d_softc;
	md = sc->sc_md;
	mdi = (struct g_raid_md_nvidia_object *)md;
	pd = (struct g_raid_md_nvidia_perdisk *)disk->d_md_data;
	pdmeta = pd->pd_meta;

	if (mdi->mdio_started) {
		if (g_raid_md_nvidia_start_disk(disk))
			g_raid_md_write_nvidia(md, NULL, NULL, NULL);
	} else {
		if (mdi->mdio_meta == NULL ||
		    mdi->mdio_meta->disk_number >= mdi->mdio_meta->total_disks) {
			G_RAID_DEBUG1(1, sc, "Newer disk");
			if (mdi->mdio_meta != NULL)
				free(mdi->mdio_meta, M_MD_NVIDIA);
			mdi->mdio_meta = nvidia_meta_copy(pdmeta);
			mdi->mdio_total_disks = pdmeta->total_disks;
			mdi->mdio_disks_present = 1;
		} else if (pdmeta->disk_number < mdi->mdio_meta->total_disks) {
			mdi->mdio_disks_present++;
			G_RAID_DEBUG1(1, sc, "Matching disk (%d of %d up)",
			    mdi->mdio_disks_present,
			    mdi->mdio_total_disks);
		} else
			G_RAID_DEBUG1(1, sc, "Spare disk");

		/* If we collected all needed disks - start array. */
		if (mdi->mdio_disks_present == mdi->mdio_total_disks)
			g_raid_md_nvidia_start(sc);
	}
}