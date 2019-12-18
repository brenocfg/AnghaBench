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
struct pci_dev {int dummy; } ;
struct mlx5_priv {int dummy; } ;
struct mlx5_core_dev {struct mlx5_priv priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  mlx5_cmd_use_polling (struct mlx5_core_dev*) ; 
 int /*<<< orphan*/  mlx5_disable_interrupts (struct mlx5_core_dev*) ; 
 int /*<<< orphan*/  mlx5_pci_disable_device (struct mlx5_core_dev*) ; 
 int mlx5_try_fast_unload (struct mlx5_core_dev*) ; 
 int /*<<< orphan*/  mlx5_unload_one (struct mlx5_core_dev*,struct mlx5_priv*,int) ; 
 struct mlx5_core_dev* pci_get_drvdata (struct pci_dev*) ; 

__attribute__((used)) static void shutdown_one(struct pci_dev *pdev)
{
	struct mlx5_core_dev *dev  = pci_get_drvdata(pdev);
	struct mlx5_priv *priv = &dev->priv;
	int err;

	/* enter polling mode */
	mlx5_cmd_use_polling(dev);

	/* disable all interrupts */
	mlx5_disable_interrupts(dev);

	err = mlx5_try_fast_unload(dev);
	if (err)
	        mlx5_unload_one(dev, priv, false);
	mlx5_pci_disable_device(dev);
}