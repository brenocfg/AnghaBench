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
struct g_raid_md_promise_pervolume {int pv_started; int /*<<< orphan*/  pv_start_co; struct g_raid_md_promise_pervolume* pv_meta; } ;
struct g_raid_md_object {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_MD_PROMISE ; 
 int /*<<< orphan*/  callout_stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (struct g_raid_md_promise_pervolume*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
g_raid_md_free_volume_promise(struct g_raid_md_object *md,
    struct g_raid_volume *vol)
{
	struct g_raid_md_promise_pervolume *pv;

	pv = (struct g_raid_md_promise_pervolume *)vol->v_md_data;
	if (pv && pv->pv_meta != NULL) {
		free(pv->pv_meta, M_MD_PROMISE);
		pv->pv_meta = NULL;
	}
	if (pv && !pv->pv_started) {
		pv->pv_started = 1;
		callout_stop(&pv->pv_start_co);
	}
	free(pv, M_MD_PROMISE);
	vol->v_md_data = NULL;
	return (0);
}