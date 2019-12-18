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
struct g_raid_md_sii_perdisk {struct g_raid_md_sii_perdisk* pd_meta; } ;
struct g_raid_md_object {int dummy; } ;
struct g_raid_disk {int /*<<< orphan*/ * d_md_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_MD_SII ; 
 int /*<<< orphan*/  free (struct g_raid_md_sii_perdisk*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
g_raid_md_free_disk_sii(struct g_raid_md_object *md,
    struct g_raid_disk *disk)
{
	struct g_raid_md_sii_perdisk *pd;

	pd = (struct g_raid_md_sii_perdisk *)disk->d_md_data;
	if (pd->pd_meta != NULL) {
		free(pd->pd_meta, M_MD_SII);
		pd->pd_meta = NULL;
	}
	free(pd, M_MD_SII);
	disk->d_md_data = NULL;
	return (0);
}