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
typedef  int u32 ;
typedef  scalar_t__ u16 ;
struct pci_dev {scalar_t__ device; } ;
struct mlx5_core_health {int /*<<< orphan*/  health_counter; } ;
struct TYPE_2__ {struct mlx5_core_health health; } ;
struct mlx5_core_dev {TYPE_1__ priv; } ;

/* Variables and functions */
 int ioread32be (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5_core_info (struct mlx5_core_dev*,char*,int,...) ; 
 int /*<<< orphan*/  mlx5_core_warn (struct mlx5_core_dev*,char*) ; 
 int /*<<< orphan*/  msleep (int) ; 
 struct mlx5_core_dev* pci_get_drvdata (struct pci_dev*) ; 
 scalar_t__ pci_read_config_word (struct pci_dev*,int,scalar_t__*) ; 

__attribute__((used)) static void wait_vital(struct pci_dev *pdev)
{
	struct mlx5_core_dev *dev = pci_get_drvdata(pdev);
	struct mlx5_core_health *health = &dev->priv.health;
	const int niter = 100;
	u32 count;
	u16 did;
	int i;

	/* Wait for firmware to be ready after reset */
	msleep(1000);
	for (i = 0; i < niter; i++) {
		if (pci_read_config_word(pdev, 2, &did)) {
			mlx5_core_warn(dev, "failed reading config word\n");
			break;
		}
		if (did == pdev->device) {
			mlx5_core_info(dev,
			    "device ID correctly read after %d iterations\n", i);
			break;
		}
		msleep(50);
	}
	if (i == niter)
		mlx5_core_warn(dev, "could not read device ID\n");

	for (i = 0; i < niter; i++) {
		count = ioread32be(health->health_counter);
		if (count && count != 0xffffffff) {
			mlx5_core_info(dev,
			"Counter value 0x%x after %d iterations\n", count, i);
			break;
		}
		msleep(50);
	}

	if (i == niter)
		mlx5_core_warn(dev, "could not read device ID\n");
}