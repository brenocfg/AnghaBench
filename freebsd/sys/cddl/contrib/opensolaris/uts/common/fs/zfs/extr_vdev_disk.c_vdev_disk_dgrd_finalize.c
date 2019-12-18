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
struct TYPE_2__ {int /*<<< orphan*/  vdev_guid; int /*<<< orphan*/  vdev_spa; } ;
typedef  TYPE_1__ vdev_t ;
typedef  int /*<<< orphan*/  ldi_handle_t ;
typedef  int /*<<< orphan*/  ldi_ev_cookie_t ;

/* Variables and functions */
 int /*<<< orphan*/  LDI_EV_DEGRADE ; 
 int /*<<< orphan*/  ldi_ev_get_type (int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vdev_degrade (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
vdev_disk_dgrd_finalize(ldi_handle_t lh, ldi_ev_cookie_t ecookie,
    int ldi_result, void *arg, void *ev_data)
{
	vdev_t *vd = (vdev_t *)arg;

	/*
	 * Ignore events other than degrade.
	 */
	if (strcmp(ldi_ev_get_type(ecookie), LDI_EV_DEGRADE) != 0)
		return;

	/*
	 * Degrade events always succeed. Mark the vdev as degraded.
	 * This status is purely informative for the user.
	 */
	(void) vdev_degrade(vd->vdev_spa, vd->vdev_guid, 0);
}