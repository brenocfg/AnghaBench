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
struct g_raid_md_object {int /*<<< orphan*/  mdo_softc; } ;
struct g_raid_md_jmicron_object {int /*<<< orphan*/ * mdio_meta; int /*<<< orphan*/ * mdio_rootmount; int /*<<< orphan*/  mdio_start_co; scalar_t__ mdio_started; } ;

/* Variables and functions */
 int /*<<< orphan*/  G_RAID_DEBUG1 (int,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  M_MD_JMICRON ; 
 int /*<<< orphan*/  callout_stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  root_mount_rel (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
g_raid_md_free_jmicron(struct g_raid_md_object *md)
{
	struct g_raid_md_jmicron_object *mdi;

	mdi = (struct g_raid_md_jmicron_object *)md;
	if (!mdi->mdio_started) {
		mdi->mdio_started = 0;
		callout_stop(&mdi->mdio_start_co);
		G_RAID_DEBUG1(1, md->mdo_softc,
		    "root_mount_rel %p", mdi->mdio_rootmount);
		root_mount_rel(mdi->mdio_rootmount);
		mdi->mdio_rootmount = NULL;
	}
	if (mdi->mdio_meta != NULL) {
		free(mdi->mdio_meta, M_MD_JMICRON);
		mdi->mdio_meta = NULL;
	}
	return (0);
}