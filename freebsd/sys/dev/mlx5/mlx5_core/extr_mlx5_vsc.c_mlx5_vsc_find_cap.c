#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct mlx5_core_dev {int vsc_addr; TYPE_2__* pdev; } ;
struct TYPE_3__ {int /*<<< orphan*/  bsddev; } ;
struct TYPE_4__ {TYPE_1__ dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCIY_VENDOR ; 
 int pci_find_cap (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

int mlx5_vsc_find_cap(struct mlx5_core_dev *mdev)
{
	int *capreg = &mdev->vsc_addr;
	int err;

	err = pci_find_cap(mdev->pdev->dev.bsddev, PCIY_VENDOR, capreg);

	if (err)
		*capreg = 0;

	return err;
}