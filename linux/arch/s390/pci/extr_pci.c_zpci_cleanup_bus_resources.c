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
struct zpci_dev {TYPE_1__* bars; } ;
struct TYPE_2__ {int /*<<< orphan*/  res; int /*<<< orphan*/  map_idx; int /*<<< orphan*/  size; } ;

/* Variables and functions */
 int PCI_BAR_COUNT ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  release_resource (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zpci_free_iomap (struct zpci_dev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void zpci_cleanup_bus_resources(struct zpci_dev *zdev)
{
	int i;

	for (i = 0; i < PCI_BAR_COUNT; i++) {
		if (!zdev->bars[i].size || !zdev->bars[i].res)
			continue;

		zpci_free_iomap(zdev, zdev->bars[i].map_idx);
		release_resource(zdev->bars[i].res);
		kfree(zdev->bars[i].res);
	}
}