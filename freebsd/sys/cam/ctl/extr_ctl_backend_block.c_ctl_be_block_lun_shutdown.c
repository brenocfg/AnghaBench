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
struct ctl_be_block_softc {int /*<<< orphan*/  lock; } ;
struct ctl_be_block_lun {int flags; struct ctl_be_block_softc* softc; } ;

/* Variables and functions */
 int CTL_BE_BLOCK_LUN_UNCONFIGURED ; 
 int CTL_BE_BLOCK_LUN_WAITING ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wakeup (struct ctl_be_block_lun*) ; 

__attribute__((used)) static void
ctl_be_block_lun_shutdown(void *be_lun)
{
	struct ctl_be_block_lun *lun = be_lun;
	struct ctl_be_block_softc *softc = lun->softc;

	mtx_lock(&softc->lock);
	lun->flags |= CTL_BE_BLOCK_LUN_UNCONFIGURED;
	if (lun->flags & CTL_BE_BLOCK_LUN_WAITING)
		wakeup(lun);
	mtx_unlock(&softc->lock);
}