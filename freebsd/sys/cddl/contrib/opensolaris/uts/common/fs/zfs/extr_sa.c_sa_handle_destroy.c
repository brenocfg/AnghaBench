#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  sa_lock; scalar_t__ sa_spill; int /*<<< orphan*/ * sa_bonus; scalar_t__ sa_spill_tab; int /*<<< orphan*/  sa_os; scalar_t__ sa_bonus_tab; int /*<<< orphan*/  sa_dbu; } ;
typedef  TYPE_1__ sa_handle_t ;
typedef  int /*<<< orphan*/  dmu_buf_t ;

/* Variables and functions */
 int /*<<< orphan*/  dmu_buf_rele (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dmu_buf_remove_user (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sa_cache ; 
 int /*<<< orphan*/  sa_idx_tab_rele (int /*<<< orphan*/ ,scalar_t__) ; 

void
sa_handle_destroy(sa_handle_t *hdl)
{
	dmu_buf_t *db = hdl->sa_bonus;

	mutex_enter(&hdl->sa_lock);
	(void) dmu_buf_remove_user(db, &hdl->sa_dbu);

	if (hdl->sa_bonus_tab)
		sa_idx_tab_rele(hdl->sa_os, hdl->sa_bonus_tab);

	if (hdl->sa_spill_tab)
		sa_idx_tab_rele(hdl->sa_os, hdl->sa_spill_tab);

	dmu_buf_rele(hdl->sa_bonus, NULL);

	if (hdl->sa_spill)
		dmu_buf_rele((dmu_buf_t *)hdl->sa_spill, NULL);
	mutex_exit(&hdl->sa_lock);

	kmem_cache_free(sa_cache, hdl);
}