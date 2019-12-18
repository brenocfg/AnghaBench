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
struct TYPE_3__ {int /*<<< orphan*/  vdev_spa; int /*<<< orphan*/  vdev_probe_wanted; } ;
typedef  TYPE_1__ vdev_t ;
typedef  int /*<<< orphan*/  ldi_handle_t ;
typedef  int /*<<< orphan*/  ldi_ev_cookie_t ;

/* Variables and functions */
 int /*<<< orphan*/  B_TRUE ; 
 int /*<<< orphan*/  LDI_EV_OFFLINE ; 
 int LDI_EV_SUCCESS ; 
 int /*<<< orphan*/  SPA_ASYNC_PROBE ; 
 int /*<<< orphan*/  ldi_ev_get_type (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spa_async_request (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vdev_disk_free (TYPE_1__*) ; 

__attribute__((used)) static void
vdev_disk_off_finalize(ldi_handle_t lh, ldi_ev_cookie_t ecookie,
    int ldi_result, void *arg, void *ev_data)
{
	vdev_t *vd = (vdev_t *)arg;

	/*
	 * Ignore events other than offline.
	 */
	if (strcmp(ldi_ev_get_type(ecookie), LDI_EV_OFFLINE) != 0)
		return;

	/*
	 * We have already closed the LDI handle in notify.
	 * Clean up the LDI event callbacks and free vd->vdev_tsd.
	 */
	vdev_disk_free(vd);

	/*
	 * Request that the vdev be reopened if the offline state change was
	 * unsuccessful.
	 */
	if (ldi_result != LDI_EV_SUCCESS) {
		vd->vdev_probe_wanted = B_TRUE;
		spa_async_request(vd->vdev_spa, SPA_ASYNC_PROBE);
	}
}