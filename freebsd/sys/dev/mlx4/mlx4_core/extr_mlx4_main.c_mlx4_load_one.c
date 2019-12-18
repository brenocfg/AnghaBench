#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
struct pci_dev {int /*<<< orphan*/  dev; int /*<<< orphan*/  revision; } ;
struct TYPE_8__ {int num_ports; int num_comp_vectors; struct mlx4_dev_cap* qp1_proxy; struct mlx4_dev_cap* qp1_tunnel; struct mlx4_dev_cap* qp0_proxy; struct mlx4_dev_cap* qp0_tunnel; struct mlx4_dev_cap* qp0_qkey; } ;
struct mlx4_dev {int flags; struct mlx4_dev_cap* dev_vfs; TYPE_4__* persist; TYPE_3__ caps; scalar_t__ num_slaves; int /*<<< orphan*/  numa_node; int /*<<< orphan*/  rev_id; } ;
struct TYPE_7__ {int port1; int port2; } ;
struct TYPE_6__ {int /*<<< orphan*/  pool_lock; int /*<<< orphan*/  pool_bm; } ;
struct TYPE_10__ {int /*<<< orphan*/  context_lock; } ;
struct mlx4_priv {struct mlx4_dev dev; int /*<<< orphan*/ * port; scalar_t__ removed; TYPE_2__ v2p; TYPE_1__ msix_ctl; int /*<<< orphan*/  opreq_task; int /*<<< orphan*/  opreq_count; int /*<<< orphan*/  bf_mutex; int /*<<< orphan*/  bf_list; TYPE_5__ cmd; int /*<<< orphan*/  pgdir_mutex; int /*<<< orphan*/  pgdir_list; int /*<<< orphan*/  bond_mutex; int /*<<< orphan*/  port_mutex; int /*<<< orphan*/  ctx_lock; int /*<<< orphan*/  ctx_list; } ;
struct mlx4_dev_cap {int flags2; int min_port; int n_ports; } ;
struct TYPE_9__ {int num_vfs; unsigned int* nvfs; int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int EACCES ; 
 int EBUSY ; 
 int EINVAL ; 
 int ENOMEM ; 
 int ENOSYS ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAX_MSIX ; 
 int /*<<< orphan*/  MLX4_CMD_CLEANUP_ALL ; 
 int /*<<< orphan*/  MLX4_CMD_CLEANUP_VHCR ; 
 int /*<<< orphan*/  MLX4_DEVICE_STATE_UP ; 
 int MLX4_DEV_CAP_FLAG2_SYS_EQS ; 
 int MLX4_FLAG_MASTER ; 
 int MLX4_FLAG_MSI_X ; 
 int MLX4_FLAG_SLAVE ; 
 int MLX4_FLAG_SRIOV ; 
 scalar_t__ MLX4_MAX_NUM_SLAVES ; 
 int MLX4_PCI_DEV_IS_VF ; 
 int /*<<< orphan*/  RES_TR_FREE_STRUCTS_ONLY ; 
 int /*<<< orphan*/  SRIOV_VALID_STATE (int) ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bitmap_zero (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_to_node (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct mlx4_dev_cap*) ; 
 struct mlx4_dev_cap* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (unsigned int*,int*,int) ; 
 int /*<<< orphan*/  memset (struct mlx4_dev_cap*,int /*<<< orphan*/ ,int) ; 
 int mlx4_ARM_COMM_CHANNEL (struct mlx4_dev*) ; 
 int mlx4_QUERY_DEV_CAP (struct mlx4_dev*,struct mlx4_dev_cap*) ; 
 int mlx4_alloc_eq_table (struct mlx4_dev*) ; 
 scalar_t__ mlx4_check_dev_cap (struct mlx4_dev*,struct mlx4_dev_cap*,int*) ; 
 int /*<<< orphan*/  mlx4_check_pcie_caps (struct mlx4_dev*) ; 
 int /*<<< orphan*/  mlx4_cleanup_counters_table (struct mlx4_dev*) ; 
 int /*<<< orphan*/  mlx4_cleanup_cq_table (struct mlx4_dev*) ; 
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
 int mlx4_cmd_init (struct mlx4_dev*) ; 
 int /*<<< orphan*/  mlx4_cmd_use_polling (struct mlx4_dev*) ; 
 int /*<<< orphan*/  mlx4_enable_msi_x (struct mlx4_dev*) ; 
 int mlx4_enable_sriov (struct mlx4_dev*,struct pci_dev*,int,int,int) ; 
 int /*<<< orphan*/  mlx4_err (struct mlx4_dev*,char*,...) ; 
 int /*<<< orphan*/  mlx4_free_eq_table (struct mlx4_dev*) ; 
 int /*<<< orphan*/  mlx4_free_ownership (struct mlx4_dev*) ; 
 int /*<<< orphan*/  mlx4_free_resource_tracker (struct mlx4_dev*,int /*<<< orphan*/ ) ; 
 int mlx4_get_ownership (struct mlx4_dev*) ; 
 int mlx4_init_fw (struct mlx4_dev*) ; 
 int mlx4_init_hca (struct mlx4_dev*) ; 
 int mlx4_init_port_info (struct mlx4_dev*,int) ; 
 int /*<<< orphan*/  mlx4_init_quotas (struct mlx4_dev*) ; 
 int mlx4_init_steering (struct mlx4_dev*) ; 
 scalar_t__ mlx4_is_master (struct mlx4_dev*) ; 
 scalar_t__ mlx4_is_mfunc (struct mlx4_dev*) ; 
 scalar_t__ mlx4_is_slave (struct mlx4_dev*) ; 
 int /*<<< orphan*/  mlx4_multi_func_cleanup (struct mlx4_dev*) ; 
 int mlx4_multi_func_init (struct mlx4_dev*) ; 
 int /*<<< orphan*/  mlx4_opreq_action ; 
 int mlx4_register_device (struct mlx4_dev*) ; 
 int /*<<< orphan*/  mlx4_request_modules (struct mlx4_dev*) ; 
 int mlx4_reset (struct mlx4_dev*) ; 
 int /*<<< orphan*/  mlx4_sense_init (struct mlx4_dev*) ; 
 int mlx4_setup_hca (struct mlx4_dev*) ; 
 int /*<<< orphan*/  mlx4_start_sense (struct mlx4_dev*) ; 
 int /*<<< orphan*/  mlx4_warn (struct mlx4_dev*,char*) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int num_vfs_argc ; 
 int /*<<< orphan*/  pci_disable_msix (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_disable_sriov (struct pci_dev*) ; 
 int pci_num_vf (struct pci_dev*) ; 
 int /*<<< orphan*/  pf_loading ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mlx4_load_one(struct pci_dev *pdev, int pci_dev_data,
			 int total_vfs, int *nvfs, struct mlx4_priv *priv,
			 int reset_flow)
{
	struct mlx4_dev *dev;
	unsigned sum = 0;
	int err;
	int port;
	int i;
	struct mlx4_dev_cap *dev_cap = NULL;
	int existing_vfs = 0;

	dev = &priv->dev;

	INIT_LIST_HEAD(&priv->ctx_list);
	spin_lock_init(&priv->ctx_lock);

	mutex_init(&priv->port_mutex);
	mutex_init(&priv->bond_mutex);

	INIT_LIST_HEAD(&priv->pgdir_list);
	mutex_init(&priv->pgdir_mutex);
	spin_lock_init(&priv->cmd.context_lock);

	INIT_LIST_HEAD(&priv->bf_list);
	mutex_init(&priv->bf_mutex);

	dev->rev_id = pdev->revision;
	dev->numa_node = dev_to_node(&pdev->dev);

	/* Detect if this device is a virtual function */
	if (pci_dev_data & MLX4_PCI_DEV_IS_VF) {
		mlx4_warn(dev, "Detected virtual function - running in slave mode\n");
		dev->flags |= MLX4_FLAG_SLAVE;
	} else {
		/* We reset the device and enable SRIOV only for physical
		 * devices.  Try to claim ownership on the device;
		 * if already taken, skip -- do not allow multiple PFs */
		err = mlx4_get_ownership(dev);
		if (err) {
			if (err < 0)
				return err;
			else {
				mlx4_warn(dev, "Multiple PFs not yet supported - Skipping PF\n");
				return -EINVAL;
			}
		}

		atomic_set(&priv->opreq_count, 0);
		INIT_WORK(&priv->opreq_task, mlx4_opreq_action);

		/*
		 * Now reset the HCA before we touch the PCI capabilities or
		 * attempt a firmware command, since a boot ROM may have left
		 * the HCA in an undefined state.
		 */
		err = mlx4_reset(dev);
		if (err) {
			mlx4_err(dev, "Failed to reset HCA, aborting\n");
			goto err_sriov;
		}

		if (total_vfs) {
			dev->flags = MLX4_FLAG_MASTER;
			existing_vfs = pci_num_vf(pdev);
			if (existing_vfs)
				dev->flags |= MLX4_FLAG_SRIOV;
			dev->persist->num_vfs = total_vfs;
		}
	}

	/* on load remove any previous indication of internal error,
	 * device is up.
	 */
	dev->persist->state = MLX4_DEVICE_STATE_UP;

slave_start:
	err = mlx4_cmd_init(dev);
	if (err) {
		mlx4_err(dev, "Failed to init command interface, aborting\n");
		goto err_sriov;
	}

	/* In slave functions, the communication channel must be initialized
	 * before posting commands. Also, init num_slaves before calling
	 * mlx4_init_hca */
	if (mlx4_is_mfunc(dev)) {
		if (mlx4_is_master(dev)) {
			dev->num_slaves = MLX4_MAX_NUM_SLAVES;

		} else {
			dev->num_slaves = 0;
			err = mlx4_multi_func_init(dev);
			if (err) {
				mlx4_err(dev, "Failed to init slave mfunc interface, aborting\n");
				goto err_cmd;
			}
		}
	}

	err = mlx4_init_fw(dev);
	if (err) {
		mlx4_err(dev, "Failed to init fw, aborting.\n");
		goto err_mfunc;
	}

	if (mlx4_is_master(dev)) {
		/* when we hit the goto slave_start below, dev_cap already initialized */
		if (!dev_cap) {
			dev_cap = kzalloc(sizeof(*dev_cap), GFP_KERNEL);

			if (!dev_cap) {
				err = -ENOMEM;
				goto err_fw;
			}

			err = mlx4_QUERY_DEV_CAP(dev, dev_cap);
			if (err) {
				mlx4_err(dev, "QUERY_DEV_CAP command failed, aborting.\n");
				goto err_fw;
			}

			if (mlx4_check_dev_cap(dev, dev_cap, nvfs))
				goto err_fw;

			if (!(dev_cap->flags2 & MLX4_DEV_CAP_FLAG2_SYS_EQS)) {
				u64 dev_flags = mlx4_enable_sriov(dev, pdev,
								  total_vfs,
								  existing_vfs,
								  reset_flow);

				mlx4_cmd_cleanup(dev, MLX4_CMD_CLEANUP_ALL);
				dev->flags = dev_flags;
				if (!SRIOV_VALID_STATE(dev->flags)) {
					mlx4_err(dev, "Invalid SRIOV state\n");
					goto err_sriov;
				}
				err = mlx4_reset(dev);
				if (err) {
					mlx4_err(dev, "Failed to reset HCA, aborting.\n");
					goto err_sriov;
				}
				goto slave_start;
			}
		} else {
			/* Legacy mode FW requires SRIOV to be enabled before
			 * doing QUERY_DEV_CAP, since max_eq's value is different if
			 * SRIOV is enabled.
			 */
			memset(dev_cap, 0, sizeof(*dev_cap));
			err = mlx4_QUERY_DEV_CAP(dev, dev_cap);
			if (err) {
				mlx4_err(dev, "QUERY_DEV_CAP command failed, aborting.\n");
				goto err_fw;
			}

			if (mlx4_check_dev_cap(dev, dev_cap, nvfs))
				goto err_fw;
		}
	}

	err = mlx4_init_hca(dev);
	if (err) {
		if (err == -EACCES) {
			/* Not primary Physical function
			 * Running in slave mode */
			mlx4_cmd_cleanup(dev, MLX4_CMD_CLEANUP_ALL);
			/* We're not a PF */
			if (dev->flags & MLX4_FLAG_SRIOV) {
				if (!existing_vfs)
					pci_disable_sriov(pdev);
				if (mlx4_is_master(dev) && !reset_flow)
					atomic_dec(&pf_loading);
				dev->flags &= ~MLX4_FLAG_SRIOV;
			}
			if (!mlx4_is_slave(dev))
				mlx4_free_ownership(dev);
			dev->flags |= MLX4_FLAG_SLAVE;
			dev->flags &= ~MLX4_FLAG_MASTER;
			goto slave_start;
		} else
			goto err_fw;
	}

	if (mlx4_is_master(dev) && (dev_cap->flags2 & MLX4_DEV_CAP_FLAG2_SYS_EQS)) {
		u64 dev_flags = mlx4_enable_sriov(dev, pdev, total_vfs,
						  existing_vfs, reset_flow);

		if ((dev->flags ^ dev_flags) & (MLX4_FLAG_MASTER | MLX4_FLAG_SLAVE)) {
			mlx4_cmd_cleanup(dev, MLX4_CMD_CLEANUP_VHCR);
			dev->flags = dev_flags;
			err = mlx4_cmd_init(dev);
			if (err) {
				/* Only VHCR is cleaned up, so could still
				 * send FW commands
				 */
				mlx4_err(dev, "Failed to init VHCR command interface, aborting\n");
				goto err_close;
			}
		} else {
			dev->flags = dev_flags;
		}

		if (!SRIOV_VALID_STATE(dev->flags)) {
			mlx4_err(dev, "Invalid SRIOV state\n");
			goto err_close;
		}
	}

	/* check if the device is functioning at its maximum possible speed.
	 * No return code for this call, just warn the user in case of PCI
	 * express device capabilities are under-satisfied by the bus.
	 */
	if (!mlx4_is_slave(dev))
		mlx4_check_pcie_caps(dev);

	/* In master functions, the communication channel must be initialized
	 * after obtaining its address from fw */
	if (mlx4_is_master(dev)) {
		if (dev->caps.num_ports < 2 &&
		    num_vfs_argc > 1) {
			err = -EINVAL;
			mlx4_err(dev,
				 "Error: Trying to configure VFs on port 2, but HCA has only %d physical ports\n",
				 dev->caps.num_ports);
			goto err_close;
		}
		memcpy(dev->persist->nvfs, nvfs, sizeof(dev->persist->nvfs));

		for (i = 0;
		     i < sizeof(dev->persist->nvfs)/
		     sizeof(dev->persist->nvfs[0]); i++) {
			unsigned j;

			for (j = 0; j < dev->persist->nvfs[i]; ++sum, ++j) {
				dev->dev_vfs[sum].min_port = i < 2 ? i + 1 : 1;
				dev->dev_vfs[sum].n_ports = i < 2 ? 1 :
					dev->caps.num_ports;
			}
		}

		/* In master functions, the communication channel
		 * must be initialized after obtaining its address from fw
		 */
		err = mlx4_multi_func_init(dev);
		if (err) {
			mlx4_err(dev, "Failed to init master mfunc interface, aborting.\n");
			goto err_close;
		}
	}

	err = mlx4_alloc_eq_table(dev);
	if (err)
		goto err_master_mfunc;

	bitmap_zero(priv->msix_ctl.pool_bm, MAX_MSIX);
	mutex_init(&priv->msix_ctl.pool_lock);

	mlx4_enable_msi_x(dev);
	if ((mlx4_is_mfunc(dev)) &&
	    !(dev->flags & MLX4_FLAG_MSI_X)) {
		err = -ENOSYS;
		mlx4_err(dev, "INTx is not supported in multi-function mode, aborting\n");
		goto err_free_eq;
	}

	if (!mlx4_is_slave(dev)) {
		err = mlx4_init_steering(dev);
		if (err)
			goto err_disable_msix;
	}

	mlx4_init_quotas(dev);

	err = mlx4_setup_hca(dev);
	if (err == -EBUSY && (dev->flags & MLX4_FLAG_MSI_X) &&
	    !mlx4_is_mfunc(dev)) {
		dev->flags &= ~MLX4_FLAG_MSI_X;
		dev->caps.num_comp_vectors = 1;
		pci_disable_msix(pdev);
		err = mlx4_setup_hca(dev);
	}

	if (err)
		goto err_steer;

	/* When PF resources are ready arm its comm channel to enable
	 * getting commands
	 */
	if (mlx4_is_master(dev)) {
		err = mlx4_ARM_COMM_CHANNEL(dev);
		if (err) {
			mlx4_err(dev, " Failed to arm comm channel eq: %x\n",
				 err);
			goto err_steer;
		}
	}

	for (port = 1; port <= dev->caps.num_ports; port++) {
		err = mlx4_init_port_info(dev, port);
		if (err)
			goto err_port;
	}

	priv->v2p.port1 = 1;
	priv->v2p.port2 = 2;

	err = mlx4_register_device(dev);
	if (err)
		goto err_port;

	mlx4_request_modules(dev);

	mlx4_sense_init(dev);
	mlx4_start_sense(dev);

	priv->removed = 0;

	if (mlx4_is_master(dev) && dev->persist->num_vfs && !reset_flow)
		atomic_dec(&pf_loading);

	kfree(dev_cap);
	return 0;

err_port:
	for (--port; port >= 1; --port)
		mlx4_cleanup_port_info(&priv->port[port]);

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
	mlx4_cleanup_uar_table(dev);

err_steer:
	if (!mlx4_is_slave(dev))
		mlx4_clear_steering(dev);

err_disable_msix:
	if (dev->flags & MLX4_FLAG_MSI_X)
		pci_disable_msix(pdev);

err_free_eq:
	mlx4_free_eq_table(dev);

err_master_mfunc:
	if (mlx4_is_master(dev)) {
		mlx4_free_resource_tracker(dev, RES_TR_FREE_STRUCTS_ONLY);
		mlx4_multi_func_cleanup(dev);
	}

	if (mlx4_is_slave(dev)) {
		kfree(dev->caps.qp0_qkey);
		kfree(dev->caps.qp0_tunnel);
		kfree(dev->caps.qp0_proxy);
		kfree(dev->caps.qp1_tunnel);
		kfree(dev->caps.qp1_proxy);
	}

err_close:
	mlx4_close_hca(dev);

err_fw:
	mlx4_close_fw(dev);

err_mfunc:
	if (mlx4_is_slave(dev))
		mlx4_multi_func_cleanup(dev);

err_cmd:
	mlx4_cmd_cleanup(dev, MLX4_CMD_CLEANUP_ALL);

err_sriov:
	if (dev->flags & MLX4_FLAG_SRIOV && !existing_vfs) {
		pci_disable_sriov(pdev);
		dev->flags &= ~MLX4_FLAG_SRIOV;
	}

	if (mlx4_is_master(dev) && dev->persist->num_vfs && !reset_flow)
		atomic_dec(&pf_loading);

	kfree(priv->dev.dev_vfs);

	if (!mlx4_is_slave(dev))
		mlx4_free_ownership(dev);

	kfree(dev_cap);
	return err;
}