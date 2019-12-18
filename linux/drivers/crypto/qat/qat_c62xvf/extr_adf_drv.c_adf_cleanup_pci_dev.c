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
struct TYPE_2__ {int /*<<< orphan*/  pci_dev; } ;
struct adf_accel_dev {TYPE_1__ accel_pci_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  pci_disable_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_release_regions (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void adf_cleanup_pci_dev(struct adf_accel_dev *accel_dev)
{
	pci_release_regions(accel_dev->accel_pci_dev.pci_dev);
	pci_disable_device(accel_dev->accel_pci_dev.pci_dev);
}