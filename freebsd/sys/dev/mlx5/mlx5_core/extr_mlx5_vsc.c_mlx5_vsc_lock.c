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
typedef  scalar_t__ u32 ;
struct mlx5_core_dev {int vsc_addr; TYPE_2__* pdev; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_3__ {int /*<<< orphan*/  bsddev; } ;
struct TYPE_4__ {TYPE_1__ dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DELAY (int) ; 
 int EBUSY ; 
 int EINVAL ; 
 scalar_t__ MLX5_VSC_COUNTER_OFFSET ; 
 int MLX5_VSC_MAX_RETRIES ; 
 scalar_t__ MLX5_VSC_SEMA_OFFSET ; 
 int /*<<< orphan*/  mlx5_core_warn (struct mlx5_core_dev*,char*) ; 
 scalar_t__ pci_read_config (int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  pci_write_config (int /*<<< orphan*/ ,scalar_t__,scalar_t__,int) ; 
 int random () ; 

int mlx5_vsc_lock(struct mlx5_core_dev *mdev)
{
	device_t dev = mdev->pdev->dev.bsddev;
	int vsc_addr = mdev->vsc_addr;
	int retries = 0;
	u32 lock_val;
	u32 counter;

	if (!vsc_addr) {
		mlx5_core_warn(mdev, "Unable to acquire vsc lock, vsc_addr not initialized\n");
		return EINVAL;
	}

	while (true) {
		if (retries > MLX5_VSC_MAX_RETRIES)
			return EBUSY;

		if (pci_read_config(dev, vsc_addr + MLX5_VSC_SEMA_OFFSET, 4)) {
			retries++;
			/*
			 * The PRM suggests random 0 - 10ms to prevent multiple
			 * waiters on the same interval in order to avoid starvation
			 */
			DELAY((random() % 9000) + 1000);
			continue;
		}

		counter = pci_read_config(dev, vsc_addr + MLX5_VSC_COUNTER_OFFSET, 4);
		pci_write_config(dev, vsc_addr + MLX5_VSC_SEMA_OFFSET, counter, 4);
		lock_val = pci_read_config(dev, vsc_addr + MLX5_VSC_SEMA_OFFSET, 4);

		if (lock_val == counter)
			break;

		retries++;
	}

	return 0;
}