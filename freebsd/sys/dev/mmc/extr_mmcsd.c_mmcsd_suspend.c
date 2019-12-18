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
struct mmcsd_softc {struct mmcsd_part** part; } ;
struct mmcsd_part {int suspend; scalar_t__ running; int ioctl; int /*<<< orphan*/  ioctl_mtx; int /*<<< orphan*/  disk_mtx; int /*<<< orphan*/ * disk; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  MMCSD_DISK_LOCK (struct mmcsd_part*) ; 
 int /*<<< orphan*/  MMCSD_DISK_UNLOCK (struct mmcsd_part*) ; 
 int /*<<< orphan*/  MMCSD_IOCTL_LOCK (struct mmcsd_part*) ; 
 int /*<<< orphan*/  MMCSD_IOCTL_UNLOCK (struct mmcsd_part*) ; 
 scalar_t__ MMC_ERR_NONE ; 
 int MMC_PART_MAX ; 
 struct mmcsd_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ mmcsd_flush_cache (struct mmcsd_softc*) ; 
 int /*<<< orphan*/  msleep (struct mmcsd_part*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wakeup (struct mmcsd_part*) ; 

__attribute__((used)) static int
mmcsd_suspend(device_t dev)
{
	struct mmcsd_softc *sc = device_get_softc(dev);
	struct mmcsd_part *part;
	int i;

	for (i = 0; i < MMC_PART_MAX; i++) {
		part = sc->part[i];
		if (part != NULL) {
			if (part->disk != NULL) {
				MMCSD_DISK_LOCK(part);
				part->suspend = 1;
				if (part->running > 0) {
					/* kill thread */
					part->running = 0;
					wakeup(part);
					/* wait for thread to finish. */
					while (part->running != -1)
						msleep(part, &part->disk_mtx, 0,
						    "mmcsd disk suspension", 0);
				}
				MMCSD_DISK_UNLOCK(part);
			}
			MMCSD_IOCTL_LOCK(part);
			while (part->ioctl > 0)
				msleep(part, &part->ioctl_mtx, 0,
				    "mmcsd IOCTL suspension", 0);
			part->ioctl = -1;
			MMCSD_IOCTL_UNLOCK(part);
		}
	}
	if (mmcsd_flush_cache(sc) != MMC_ERR_NONE)
		device_printf(dev, "failed to flush cache\n");
	return (0);
}