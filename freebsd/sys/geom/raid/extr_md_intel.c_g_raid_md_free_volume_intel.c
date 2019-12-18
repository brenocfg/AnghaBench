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
struct g_raid_volume {int /*<<< orphan*/ * v_md_data; } ;
struct g_raid_md_object {int dummy; } ;
struct g_raid_md_intel_pervolume {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_MD_INTEL ; 
 int /*<<< orphan*/  free (struct g_raid_md_intel_pervolume*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
g_raid_md_free_volume_intel(struct g_raid_md_object *md,
    struct g_raid_volume *vol)
{
	struct g_raid_md_intel_pervolume *pv;

	pv = (struct g_raid_md_intel_pervolume *)vol->v_md_data;
	free(pv, M_MD_INTEL);
	vol->v_md_data = NULL;
	return (0);
}