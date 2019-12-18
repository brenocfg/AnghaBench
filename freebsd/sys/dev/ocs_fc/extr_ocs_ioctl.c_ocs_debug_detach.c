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
struct ocs_softc {TYPE_1__* cdev; int /*<<< orphan*/  dbg_lock; } ;
struct TYPE_2__ {int /*<<< orphan*/ * si_drv1; } ;

/* Variables and functions */
 int /*<<< orphan*/  destroy_dev (TYPE_1__*) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 

void
ocs_debug_detach(void *os)
{
	struct ocs_softc *ocs = os;

	mtx_destroy(&ocs->dbg_lock);

	if (ocs->cdev) {
		ocs->cdev->si_drv1 = NULL;
		destroy_dev(ocs->cdev);
	}
}