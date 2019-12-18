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
struct mmcsd_part {scalar_t__ running; scalar_t__ ioctl; int /*<<< orphan*/  cnt; int /*<<< orphan*/  name; int /*<<< orphan*/  p; scalar_t__ suspend; int /*<<< orphan*/ * disk; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  MMCSD_DISK_LOCK (struct mmcsd_part*) ; 
 int /*<<< orphan*/  MMCSD_DISK_UNLOCK (struct mmcsd_part*) ; 
 int /*<<< orphan*/  MMCSD_IOCTL_LOCK (struct mmcsd_part*) ; 
 int /*<<< orphan*/  MMCSD_IOCTL_UNLOCK (struct mmcsd_part*) ; 
 int MMC_PART_MAX ; 
 struct mmcsd_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kproc_create (int /*<<< orphan*/ *,struct mmcsd_part*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmcsd_task ; 

__attribute__((used)) static int
mmcsd_resume(device_t dev)
{
	struct mmcsd_softc *sc = device_get_softc(dev);
	struct mmcsd_part *part;
	int i;

	for (i = 0; i < MMC_PART_MAX; i++) {
		part = sc->part[i];
		if (part != NULL) {
			if (part->disk != NULL) {
				MMCSD_DISK_LOCK(part);
				part->suspend = 0;
				if (part->running <= 0) {
					part->running = 1;
					MMCSD_DISK_UNLOCK(part);
					kproc_create(&mmcsd_task, part,
					    &part->p, 0, 0, "%s%d: mmc/sd card",
					    part->name, part->cnt);
				} else
					MMCSD_DISK_UNLOCK(part);
			}
			MMCSD_IOCTL_LOCK(part);
			part->ioctl = 0;
			MMCSD_IOCTL_UNLOCK(part);
		}
	}
	return (0);
}