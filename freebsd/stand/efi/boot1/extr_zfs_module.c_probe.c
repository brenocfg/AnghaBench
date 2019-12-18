#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  spa_t ;
struct TYPE_9__ {int /*<<< orphan*/ * devdata; } ;
typedef  TYPE_1__ dev_info_t ;
typedef  int /*<<< orphan*/  EFI_STATUS ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (char*) ; 
 int /*<<< orphan*/  EFI_OUT_OF_RESOURCES ; 
 int /*<<< orphan*/  EFI_SUCCESS ; 
 int /*<<< orphan*/  EFI_UNSUPPORTED ; 
 int /*<<< orphan*/  add_device (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  devices ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 TYPE_1__* malloc (int) ; 
 int /*<<< orphan*/  memcpy (TYPE_1__*,TYPE_1__*,int) ; 
 scalar_t__ vdev_probe (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  vdev_read ; 

__attribute__((used)) static EFI_STATUS
probe(dev_info_t *dev)
{
	spa_t *spa;
	dev_info_t *tdev;

	/* ZFS consumes the dev on success so we need a copy. */
	tdev = malloc(sizeof(*dev));
	if (tdev == NULL) {
		DPRINTF("Failed to allocate tdev\n");
		return (EFI_OUT_OF_RESOURCES);
	}
	memcpy(tdev, dev, sizeof(*dev));

	if (vdev_probe(vdev_read, tdev, &spa) != 0) {
		free(tdev);
		return (EFI_UNSUPPORTED);
	}

	dev->devdata = spa;
	add_device(&devices, dev);

	return (EFI_SUCCESS);
}