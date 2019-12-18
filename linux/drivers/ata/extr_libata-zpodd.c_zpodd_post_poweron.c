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
struct zpodd {int powered_off; int from_notify; scalar_t__ mech_type; int zp_sampled; int zp_ready; } ;
struct ata_device {int /*<<< orphan*/  sdev; struct zpodd* zpodd; } ;

/* Variables and functions */
 scalar_t__ ODD_MECH_TYPE_DRAWER ; 
 int /*<<< orphan*/  eject_tray (struct ata_device*) ; 
 int /*<<< orphan*/  sdev_enable_disk_events (int /*<<< orphan*/ ) ; 

void zpodd_post_poweron(struct ata_device *dev)
{
	struct zpodd *zpodd = dev->zpodd;

	if (!zpodd->powered_off)
		return;

	zpodd->powered_off = false;

	if (zpodd->from_notify) {
		zpodd->from_notify = false;
		if (zpodd->mech_type == ODD_MECH_TYPE_DRAWER)
			eject_tray(dev);
	}

	zpodd->zp_sampled = false;
	zpodd->zp_ready = false;

	sdev_enable_disk_events(dev->sdev);
}