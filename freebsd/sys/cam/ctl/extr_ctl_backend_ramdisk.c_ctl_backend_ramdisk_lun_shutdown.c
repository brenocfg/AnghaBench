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
struct ctl_be_ramdisk_softc {int /*<<< orphan*/  lock; int /*<<< orphan*/  num_luns; int /*<<< orphan*/  lun_list; } ;
struct ctl_be_ramdisk_lun {int flags; struct ctl_be_ramdisk_softc* softc; } ;

/* Variables and functions */
 int CTL_BE_RAMDISK_LUN_UNCONFIGURED ; 
 int CTL_BE_RAMDISK_LUN_WAITING ; 
 int /*<<< orphan*/  M_RAMDISK ; 
 int /*<<< orphan*/  STAILQ_REMOVE (int /*<<< orphan*/ *,struct ctl_be_ramdisk_lun*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ctl_be_ramdisk_lun ; 
 int /*<<< orphan*/  free (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  links ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wakeup (struct ctl_be_ramdisk_lun*) ; 

__attribute__((used)) static void
ctl_backend_ramdisk_lun_shutdown(void *be_lun)
{
	struct ctl_be_ramdisk_lun *lun = be_lun;
	struct ctl_be_ramdisk_softc *softc = lun->softc;

	mtx_lock(&softc->lock);
	lun->flags |= CTL_BE_RAMDISK_LUN_UNCONFIGURED;
	if (lun->flags & CTL_BE_RAMDISK_LUN_WAITING) {
		wakeup(lun);
	} else {
		STAILQ_REMOVE(&softc->lun_list, lun, ctl_be_ramdisk_lun,
			      links);
		softc->num_luns--;
		free(be_lun, M_RAMDISK);
	}
	mtx_unlock(&softc->lock);
}