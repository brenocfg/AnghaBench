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
struct pci_dev {int dummy; } ;
struct mlx4_priv {int removed; int pci_dev_data; int /*<<< orphan*/  driver_uar; int /*<<< orphan*/  kar; int /*<<< orphan*/ * port; } ;
struct mlx4_dev_persistent {struct mlx4_dev* dev; } ;
struct TYPE_4__ {int num_ports; int /*<<< orphan*/  qp1_proxy; int /*<<< orphan*/  qp1_tunnel; int /*<<< orphan*/  qp0_proxy; int /*<<< orphan*/  qp0_tunnel; int /*<<< orphan*/  qp0_qkey; int /*<<< orphan*/ * possible_type; int /*<<< orphan*/ * port_type; } ;
struct mlx4_dev {int flags; int /*<<< orphan*/  dev_vfs; TYPE_2__ caps; TYPE_1__* persist; } ;
struct TYPE_3__ {int /*<<< orphan*/ * curr_port_poss_type; int /*<<< orphan*/ * curr_port_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLX4_CMD_CLEANUP_ALL ; 
 int MLX4_FLAG_MSI_X ; 
 int /*<<< orphan*/  RES_TR_FREE_SLAVES_ONLY ; 
 int /*<<< orphan*/  RES_TR_FREE_STRUCTS_ONLY ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx4_CLOSE_PORT (struct mlx4_dev*,int) ; 
 int /*<<< orphan*/  mlx4_clean_dev (struct mlx4_dev*) ; 
 int /*<<< orphan*/  mlx4_cleanup_counters_table (struct mlx4_dev*) ; 
 int /*<<< orphan*/  mlx4_cleanup_cq_table (struct mlx4_dev*) ; 
 int /*<<< orphan*/  mlx4_cleanup_default_counters (struct mlx4_dev*) ; 
 int /*<<< orphan*/  mlx4_cleanup_eq_table (struct mlx4_dev*) ; 
 int /*<<< orphan*/  mlx4_cleanup_mcg_table (struct mlx4_dev*) ; 
 int /*<<< orphan*/  mlx4_cleanup_mr_table (struct mlx4_dev*) ; 
 int /*<<< orphan*/  mlx4_cleanup_pd_table (struct mlx4_dev*) ; 
 int /*<<< orphan*/  mlx4_cleanup_port_info (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlx4_cleanup_qp_table (struct mlx4_dev*) ; 
 int /*<<< orphan*/  mlx4_cleanup_srq_table (struct mlx4_dev*) ; 
 int /*<<< orphan*/  mlx4_cleanup_uar_table (struct mlx4_dev*) ; 
 int /*<<< orphan*/  mlx4_cleanup_xrcd_table (struct mlx4_dev*) ; 
 int /*<<< orphan*/  mlx4_clear_steering (struct mlx4_dev*) ; 
 int /*<<< orphan*/  mlx4_close_fw (struct mlx4_dev*) ; 
 int /*<<< orphan*/  mlx4_close_hca (struct mlx4_dev*) ; 
 int /*<<< orphan*/  mlx4_cmd_cleanup (struct mlx4_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx4_cmd_use_polling (struct mlx4_dev*) ; 
 int /*<<< orphan*/  mlx4_free_eq_table (struct mlx4_dev*) ; 
 int /*<<< orphan*/  mlx4_free_ownership (struct mlx4_dev*) ; 
 int /*<<< orphan*/  mlx4_free_resource_tracker (struct mlx4_dev*,int /*<<< orphan*/ ) ; 
 scalar_t__ mlx4_is_master (struct mlx4_dev*) ; 
 scalar_t__ mlx4_is_slave (struct mlx4_dev*) ; 
 int /*<<< orphan*/  mlx4_multi_func_cleanup (struct mlx4_dev*) ; 
 struct mlx4_priv* mlx4_priv (struct mlx4_dev*) ; 
 int /*<<< orphan*/  mlx4_stop_sense (struct mlx4_dev*) ; 
 int /*<<< orphan*/  mlx4_uar_free (struct mlx4_dev*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlx4_unregister_device (struct mlx4_dev*) ; 
 int /*<<< orphan*/  pci_disable_msix (struct pci_dev*) ; 
 struct mlx4_dev_persistent* pci_get_drvdata (struct pci_dev*) ; 

__attribute__((used)) static void mlx4_unload_one(struct pci_dev *pdev)
{
	struct mlx4_dev_persistent *persist = pci_get_drvdata(pdev);
	struct mlx4_dev  *dev  = persist->dev;
	struct mlx4_priv *priv = mlx4_priv(dev);
	int               pci_dev_data;
	int p, i;

	if (priv->removed)
		return;

	/* saving current ports type for further use */
	for (i = 0; i < dev->caps.num_ports; i++) {
		dev->persist->curr_port_type[i] = dev->caps.port_type[i + 1];
		dev->persist->curr_port_poss_type[i] = dev->caps.
						       possible_type[i + 1];
	}

	pci_dev_data = priv->pci_dev_data;

	mlx4_stop_sense(dev);
	mlx4_unregister_device(dev);

	for (p = 1; p <= dev->caps.num_ports; p++) {
		mlx4_cleanup_port_info(&priv->port[p]);
		mlx4_CLOSE_PORT(dev, p);
	}

	if (mlx4_is_master(dev))
		mlx4_free_resource_tracker(dev,
					   RES_TR_FREE_SLAVES_ONLY);

	mlx4_cleanup_default_counters(dev);
	if (!mlx4_is_slave(dev))
		mlx4_cleanup_counters_table(dev);
	mlx4_cleanup_qp_table(dev);
	mlx4_cleanup_srq_table(dev);
	mlx4_cleanup_cq_table(dev);
	mlx4_cmd_use_polling(dev);
	mlx4_cleanup_eq_table(dev);
	mlx4_cleanup_mcg_table(dev);
	mlx4_cleanup_mr_table(dev);
	mlx4_cleanup_xrcd_table(dev);
	mlx4_cleanup_pd_table(dev);

	if (mlx4_is_master(dev))
		mlx4_free_resource_tracker(dev,
					   RES_TR_FREE_STRUCTS_ONLY);

	iounmap(priv->kar);
	mlx4_uar_free(dev, &priv->driver_uar);
	mlx4_cleanup_uar_table(dev);
	if (!mlx4_is_slave(dev))
		mlx4_clear_steering(dev);
	mlx4_free_eq_table(dev);
	if (mlx4_is_master(dev))
		mlx4_multi_func_cleanup(dev);
	mlx4_close_hca(dev);
	mlx4_close_fw(dev);
	if (mlx4_is_slave(dev))
		mlx4_multi_func_cleanup(dev);
	mlx4_cmd_cleanup(dev, MLX4_CMD_CLEANUP_ALL);

	if (dev->flags & MLX4_FLAG_MSI_X)
		pci_disable_msix(pdev);

	if (!mlx4_is_slave(dev))
		mlx4_free_ownership(dev);

	kfree(dev->caps.qp0_qkey);
	kfree(dev->caps.qp0_tunnel);
	kfree(dev->caps.qp0_proxy);
	kfree(dev->caps.qp1_tunnel);
	kfree(dev->caps.qp1_proxy);
	kfree(dev->dev_vfs);

	mlx4_clean_dev(dev);
	priv->pci_dev_data = pci_dev_data;
	priv->removed = 1;
}