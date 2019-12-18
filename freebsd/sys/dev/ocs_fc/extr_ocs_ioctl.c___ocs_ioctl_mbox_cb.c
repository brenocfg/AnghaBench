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
typedef  int /*<<< orphan*/  uint8_t ;
struct ocs_softc {int /*<<< orphan*/  dbg_lock; } ;
typedef  int /*<<< orphan*/  ocs_hw_t ;
typedef  int /*<<< orphan*/  int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wakeup (void*) ; 

__attribute__((used)) static int32_t
__ocs_ioctl_mbox_cb(ocs_hw_t *hw, int32_t status, uint8_t *mqe, void *arg)
{
	struct ocs_softc *ocs = arg;

	/* wait for the ioctl to sleep before calling wakeup */
	mtx_lock(&ocs->dbg_lock);

	mtx_unlock(&ocs->dbg_lock);

	wakeup(arg);

	return 0;
}