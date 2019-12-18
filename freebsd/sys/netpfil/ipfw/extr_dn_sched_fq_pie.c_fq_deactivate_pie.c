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
struct pie_status {int sflags; int /*<<< orphan*/  lock_mtx; int /*<<< orphan*/  aqm_pie_callout; } ;

/* Variables and functions */
 int PIE_ACTIVE ; 
 int PIE_INMEASUREMENT ; 
 int /*<<< orphan*/  callout_stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) __inline static void
fq_deactivate_pie(struct pie_status *pst)
{ 
	mtx_lock(&pst->lock_mtx);
	pst->sflags &= ~(PIE_ACTIVE | PIE_INMEASUREMENT);
	callout_stop(&pst->aqm_pie_callout);
	//D("PIE Deactivated");
	mtx_unlock(&pst->lock_mtx);
}