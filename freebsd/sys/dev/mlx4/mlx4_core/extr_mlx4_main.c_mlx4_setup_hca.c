#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {scalar_t__ pfn; } ;
struct TYPE_12__ {TYPE_3__* slave_state; } ;
struct TYPE_13__ {TYPE_4__ master; } ;
struct TYPE_10__ {TYPE_1__* eq; } ;
struct mlx4_priv {TYPE_7__ driver_uar; int /*<<< orphan*/  kar; TYPE_5__ mfunc; TYPE_2__ eq_table; } ;
struct TYPE_14__ {int num_ports; int* pkey_table_len; int /*<<< orphan*/ * port_ib_mtu; void** ib_port_def_cap; } ;
struct mlx4_dev {int flags; int num_slaves; TYPE_6__ caps; } ;
typedef  int phys_addr_t ;
typedef  void* __be32 ;
struct TYPE_11__ {void** ib_cap_mask; } ;
struct TYPE_9__ {int irq; } ;

/* Variables and functions */
 int ENOENT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  IB_MTU_2048 ; 
 int /*<<< orphan*/  IB_MTU_4096 ; 
 size_t MLX4_EQ_ASYNC ; 
 int MLX4_FLAG_MSI_X ; 
 int PAGE_SHIFT ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  ioremap (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int mlx4_NOP (struct mlx4_dev*) ; 
 int mlx4_SET_PORT (struct mlx4_dev*,int,int) ; 
 int mlx4_allocate_default_counters (struct mlx4_dev*) ; 
 int /*<<< orphan*/  mlx4_cleanup_counters_table (struct mlx4_dev*) ; 
 int /*<<< orphan*/  mlx4_cleanup_cq_table (struct mlx4_dev*) ; 
 int /*<<< orphan*/  mlx4_cleanup_default_counters (struct mlx4_dev*) ; 
 int /*<<< orphan*/  mlx4_cleanup_eq_table (struct mlx4_dev*) ; 
 int /*<<< orphan*/  mlx4_cleanup_mcg_table (struct mlx4_dev*) ; 
 int /*<<< orphan*/  mlx4_cleanup_mr_table (struct mlx4_dev*) ; 
 int /*<<< orphan*/  mlx4_cleanup_pd_table (struct mlx4_dev*) ; 
 int /*<<< orphan*/  mlx4_cleanup_qp_table (struct mlx4_dev*) ; 
 int /*<<< orphan*/  mlx4_cleanup_srq_table (struct mlx4_dev*) ; 
 int /*<<< orphan*/  mlx4_cleanup_uar_table (struct mlx4_dev*) ; 
 int /*<<< orphan*/  mlx4_cleanup_xrcd_table (struct mlx4_dev*) ; 
 int mlx4_cmd_use_events (struct mlx4_dev*) ; 
 int /*<<< orphan*/  mlx4_cmd_use_polling (struct mlx4_dev*) ; 
 int mlx4_config_mad_demux (struct mlx4_dev*) ; 
 int /*<<< orphan*/  mlx4_dbg (struct mlx4_dev*,char*) ; 
 int /*<<< orphan*/  mlx4_err (struct mlx4_dev*,char*,...) ; 
 int mlx4_get_port_ib_caps (struct mlx4_dev*,int,void**) ; 
 int mlx4_init_counters_table (struct mlx4_dev*) ; 
 int mlx4_init_cq_table (struct mlx4_dev*) ; 
 int mlx4_init_eq_table (struct mlx4_dev*) ; 
 int mlx4_init_mcg_table (struct mlx4_dev*) ; 
 int mlx4_init_mr_table (struct mlx4_dev*) ; 
 int mlx4_init_pd_table (struct mlx4_dev*) ; 
 int mlx4_init_qp_table (struct mlx4_dev*) ; 
 int mlx4_init_srq_table (struct mlx4_dev*) ; 
 int mlx4_init_uar_table (struct mlx4_dev*) ; 
 int mlx4_init_xrcd_table (struct mlx4_dev*) ; 
 scalar_t__ mlx4_is_master (struct mlx4_dev*) ; 
 scalar_t__ mlx4_is_mfunc (struct mlx4_dev*) ; 
 int /*<<< orphan*/  mlx4_is_slave (struct mlx4_dev*) ; 
 int mlx4_master_func_num (struct mlx4_dev*) ; 
 struct mlx4_priv* mlx4_priv (struct mlx4_dev*) ; 
 int mlx4_uar_alloc (struct mlx4_dev*,TYPE_7__*) ; 
 int /*<<< orphan*/  mlx4_uar_free (struct mlx4_dev*,TYPE_7__*) ; 
 int /*<<< orphan*/  mlx4_warn (struct mlx4_dev*,char*,...) ; 

__attribute__((used)) static int mlx4_setup_hca(struct mlx4_dev *dev)
{
	struct mlx4_priv *priv = mlx4_priv(dev);
	int err;
	int port;
	__be32 ib_port_default_caps;

	err = mlx4_init_uar_table(dev);
	if (err) {
		mlx4_err(dev, "Failed to initialize user access region table, aborting\n");
		return err;
	}

	err = mlx4_uar_alloc(dev, &priv->driver_uar);
	if (err) {
		mlx4_err(dev, "Failed to allocate driver access region, aborting\n");
		goto err_uar_table_free;
	}

	priv->kar = ioremap((phys_addr_t) priv->driver_uar.pfn << PAGE_SHIFT, PAGE_SIZE);
	if (!priv->kar) {
		mlx4_err(dev, "Couldn't map kernel access region, aborting\n");
		err = -ENOMEM;
		goto err_uar_free;
	}

	err = mlx4_init_pd_table(dev);
	if (err) {
		mlx4_err(dev, "Failed to initialize protection domain table, aborting\n");
		goto err_kar_unmap;
	}

	err = mlx4_init_xrcd_table(dev);
	if (err) {
		mlx4_err(dev, "Failed to initialize reliable connection domain table, aborting\n");
		goto err_pd_table_free;
	}

	err = mlx4_init_mr_table(dev);
	if (err) {
		mlx4_err(dev, "Failed to initialize memory region table, aborting\n");
		goto err_xrcd_table_free;
	}

	if (!mlx4_is_slave(dev)) {
		err = mlx4_init_mcg_table(dev);
		if (err) {
			mlx4_err(dev, "Failed to initialize multicast group table, aborting\n");
			goto err_mr_table_free;
		}
		err = mlx4_config_mad_demux(dev);
		if (err) {
			mlx4_err(dev, "Failed in config_mad_demux, aborting\n");
			goto err_mcg_table_free;
		}
	}

	err = mlx4_init_eq_table(dev);
	if (err) {
		mlx4_err(dev, "Failed to initialize event queue table, aborting\n");
		goto err_mcg_table_free;
	}

	err = mlx4_cmd_use_events(dev);
	if (err) {
		mlx4_err(dev, "Failed to switch to event-driven firmware commands, aborting\n");
		goto err_eq_table_free;
	}

	err = mlx4_NOP(dev);
	if (err) {
		if (dev->flags & MLX4_FLAG_MSI_X) {
			mlx4_warn(dev, "NOP command failed to generate MSI-X interrupt IRQ %d)\n",
				  priv->eq_table.eq[MLX4_EQ_ASYNC].irq);
			mlx4_warn(dev, "Trying again without MSI-X\n");
		} else {
			mlx4_err(dev, "NOP command failed to generate interrupt (IRQ %d), aborting\n",
				 priv->eq_table.eq[MLX4_EQ_ASYNC].irq);
			mlx4_err(dev, "BIOS or ACPI interrupt routing problem?\n");
		}

		goto err_cmd_poll;
	}

	mlx4_dbg(dev, "NOP command IRQ test passed\n");

	err = mlx4_init_cq_table(dev);
	if (err) {
		mlx4_err(dev, "Failed to initialize completion queue table, aborting\n");
		goto err_cmd_poll;
	}

	err = mlx4_init_srq_table(dev);
	if (err) {
		mlx4_err(dev, "Failed to initialize shared receive queue table, aborting\n");
		goto err_cq_table_free;
	}

	err = mlx4_init_qp_table(dev);
	if (err) {
		mlx4_err(dev, "Failed to initialize queue pair table, aborting\n");
		goto err_srq_table_free;
	}

	if (!mlx4_is_slave(dev)) {
		err = mlx4_init_counters_table(dev);
		if (err && err != -ENOENT) {
			mlx4_err(dev, "Failed to initialize counters table, aborting\n");
			goto err_qp_table_free;
		}
	}

	err = mlx4_allocate_default_counters(dev);
	if (err) {
		mlx4_err(dev, "Failed to allocate default counters, aborting\n");
		goto err_counters_table_free;
	}

	if (!mlx4_is_slave(dev)) {
		for (port = 1; port <= dev->caps.num_ports; port++) {
			ib_port_default_caps = 0;
			err = mlx4_get_port_ib_caps(dev, port,
						    &ib_port_default_caps);
			if (err)
				mlx4_warn(dev, "failed to get port %d default ib capabilities (%d). Continuing with caps = 0\n",
					  port, err);
			dev->caps.ib_port_def_cap[port] = ib_port_default_caps;

			/* initialize per-slave default ib port capabilities */
			if (mlx4_is_master(dev)) {
				int i;
				for (i = 0; i < dev->num_slaves; i++) {
					if (i == mlx4_master_func_num(dev))
						continue;
					priv->mfunc.master.slave_state[i].ib_cap_mask[port] =
						ib_port_default_caps;
				}
			}

			if (mlx4_is_mfunc(dev))
				dev->caps.port_ib_mtu[port] = IB_MTU_2048;
			else
				dev->caps.port_ib_mtu[port] = IB_MTU_4096;

			err = mlx4_SET_PORT(dev, port, mlx4_is_master(dev) ?
					    dev->caps.pkey_table_len[port] : -1);
			if (err) {
				mlx4_err(dev, "Failed to set port %d, aborting\n",
					 port);
				goto err_default_countes_free;
			}
		}
	}

	return 0;

err_default_countes_free:
	mlx4_cleanup_default_counters(dev);

err_counters_table_free:
	if (!mlx4_is_slave(dev))
		mlx4_cleanup_counters_table(dev);

err_qp_table_free:
	mlx4_cleanup_qp_table(dev);

err_srq_table_free:
	mlx4_cleanup_srq_table(dev);

err_cq_table_free:
	mlx4_cleanup_cq_table(dev);

err_cmd_poll:
	mlx4_cmd_use_polling(dev);

err_eq_table_free:
	mlx4_cleanup_eq_table(dev);

err_mcg_table_free:
	if (!mlx4_is_slave(dev))
		mlx4_cleanup_mcg_table(dev);

err_mr_table_free:
	mlx4_cleanup_mr_table(dev);

err_xrcd_table_free:
	mlx4_cleanup_xrcd_table(dev);

err_pd_table_free:
	mlx4_cleanup_pd_table(dev);

err_kar_unmap:
	iounmap(priv->kar);

err_uar_free:
	mlx4_uar_free(dev, &priv->driver_uar);

err_uar_table_free:
	mlx4_cleanup_uar_table(dev);
	return err;
}