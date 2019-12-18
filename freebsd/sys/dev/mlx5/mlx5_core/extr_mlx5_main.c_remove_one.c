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
struct mlx5_core_dev {int /*<<< orphan*/  sysctl_ctx; int /*<<< orphan*/  dump_lock; struct mlx5_priv priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct mlx5_core_dev*) ; 
 int /*<<< orphan*/  mlx5_core_err (struct mlx5_core_dev*,char*) ; 
 int /*<<< orphan*/  mlx5_fwdump_clean (struct mlx5_core_dev*) ; 
 int /*<<< orphan*/  mlx5_health_cleanup (struct mlx5_core_dev*) ; 
 int /*<<< orphan*/  mlx5_pagealloc_cleanup (struct mlx5_core_dev*) ; 
 int /*<<< orphan*/  mlx5_pci_close (struct mlx5_core_dev*,struct mlx5_priv*) ; 
 scalar_t__ mlx5_unload_one (struct mlx5_core_dev*,struct mlx5_priv*,int) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 struct mlx5_core_dev* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_set_drvdata (struct pci_dev*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sysctl_ctx_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void remove_one(struct pci_dev *pdev)
{
	struct mlx5_core_dev *dev  = pci_get_drvdata(pdev);
	struct mlx5_priv *priv = &dev->priv;

	if (mlx5_unload_one(dev, priv, true)) {
		mlx5_core_err(dev, "mlx5_unload_one failed\n");
		mlx5_health_cleanup(dev);
		return;
	}

	mlx5_pagealloc_cleanup(dev);
	mlx5_health_cleanup(dev);
	mlx5_fwdump_clean(dev);
	mlx5_pci_close(dev, priv);
	mtx_destroy(&dev->dump_lock);
	pci_set_drvdata(pdev, NULL);
	sysctl_ctx_free(&dev->sysctl_ctx);
	kfree(dev);
}