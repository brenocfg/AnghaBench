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
typedef  int u64 ;
struct mlx4_profile {int /*<<< orphan*/  num_mcg; } ;
struct TYPE_3__ {int /*<<< orphan*/  inta_pin; } ;
struct mlx4_priv {TYPE_1__ eq_table; } ;
struct mlx4_init_hca_param {int log_uar_sz; int /*<<< orphan*/  hca_core_clock; scalar_t__ mw_enabled; void* uar_page_sz; } ;
struct mlx4_dev_cap {int flags2; int /*<<< orphan*/  reserved_uars; int /*<<< orphan*/  reserved_eqs; int /*<<< orphan*/  max_eqs; } ;
struct TYPE_4__ {scalar_t__ dmfs_high_steer_mode; scalar_t__ steering_mode; int max_fmr_maps; int flags; int bmme_flags; int flags2; int /*<<< orphan*/  qp1_proxy; int /*<<< orphan*/  qp1_tunnel; int /*<<< orphan*/  qp0_proxy; int /*<<< orphan*/  qp0_tunnel; int /*<<< orphan*/  qp0_qkey; int /*<<< orphan*/ * rx_checksum_flags_port; int /*<<< orphan*/  dmfs_high_rate_qpn_range; int /*<<< orphan*/ * reserved_qps_cnt; int /*<<< orphan*/  dmfs_high_rate_qpn_base; int /*<<< orphan*/  hca_core_clock; int /*<<< orphan*/  reserved_uars; int /*<<< orphan*/  reserved_eqs; int /*<<< orphan*/  num_eqs; int /*<<< orphan*/  num_uars; int /*<<< orphan*/  num_mpts; int /*<<< orphan*/  function_caps; } ;
struct mlx4_dev {TYPE_2__ caps; int /*<<< orphan*/  board_id; } ;
struct mlx4_config_dev_params {int /*<<< orphan*/  rx_csum_flags_port_2; int /*<<< orphan*/  rx_csum_flags_port_1; } ;
struct mlx4_adapter {int /*<<< orphan*/  board_id; int /*<<< orphan*/  inta_pin; } ;
typedef  int /*<<< orphan*/  init_hca ;

/* Variables and functions */
 void* DEFAULT_UAR_PAGE_SHIFT ; 
 int EAGAIN ; 
 int ENOTSUPP ; 
 scalar_t__ INIT_HCA_TPT_MW_ENABLE ; 
 int /*<<< orphan*/  MLX4_A0_STEERING_TABLE_SIZE ; 
 int MLX4_BMME_FLAG_TYPE_2_WIN ; 
 int MLX4_DEV_CAP_FLAG2_SYS_EQS ; 
 int MLX4_DEV_CAP_FLAG2_TS ; 
 int MLX4_DEV_CAP_FLAG_MEM_WINDOW ; 
 int /*<<< orphan*/  MLX4_FS_NUM_MCG ; 
 int /*<<< orphan*/  MLX4_FUNC_CAP_DMFS_A0_STATIC ; 
 size_t MLX4_QP_REGION_FW ; 
 int MLX4_QUERY_FUNC_NUM_SYS_EQS ; 
 scalar_t__ MLX4_STEERING_DMFS_A0_DISABLE ; 
 scalar_t__ MLX4_STEERING_DMFS_A0_NOT_SUPPORTED ; 
 scalar_t__ MLX4_STEERING_DMFS_A0_STATIC ; 
 scalar_t__ MLX4_STEERING_MODE_DEVICE_MANAGED ; 
 void* PAGE_SHIFT ; 
 int /*<<< orphan*/  choose_steering_mode (struct mlx4_dev*,struct mlx4_dev_cap*) ; 
 int /*<<< orphan*/  choose_tunnel_offload_mode (struct mlx4_dev*,struct mlx4_dev_cap*) ; 
 struct mlx4_profile default_profile ; 
 int /*<<< orphan*/  dmfs_high_rate_steering_mode_str (scalar_t__) ; 
 scalar_t__ enable_4k_uar ; 
 int ilog2 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 struct mlx4_profile low_mem_profile ; 
 scalar_t__ map_bf_area (struct mlx4_dev*) ; 
 scalar_t__ map_internal_clock (struct mlx4_dev*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (struct mlx4_init_hca_param*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mlx4_CLOSE_HCA (struct mlx4_dev*,int /*<<< orphan*/ ) ; 
 int mlx4_INIT_HCA (struct mlx4_dev*,struct mlx4_init_hca_param*) ; 
 int mlx4_QUERY_ADAPTER (struct mlx4_dev*,struct mlx4_adapter*) ; 
 int mlx4_QUERY_HCA (struct mlx4_dev*,struct mlx4_init_hca_param*) ; 
 int mlx4_config_dev_retrieval (struct mlx4_dev*,struct mlx4_config_dev_params*) ; 
 int /*<<< orphan*/  mlx4_dbg (struct mlx4_dev*,char*,...) ; 
 int mlx4_dev_cap (struct mlx4_dev*,struct mlx4_dev_cap*) ; 
 int /*<<< orphan*/  mlx4_err (struct mlx4_dev*,char*) ; 
 int /*<<< orphan*/  mlx4_free_icms (struct mlx4_dev*) ; 
 int mlx4_get_phys_port_id (struct mlx4_dev*) ; 
 int /*<<< orphan*/  mlx4_info (struct mlx4_dev*,char*) ; 
 int mlx4_init_icm (struct mlx4_dev*,struct mlx4_dev_cap*,struct mlx4_init_hca_param*,int) ; 
 int mlx4_init_slave (struct mlx4_dev*) ; 
 scalar_t__ mlx4_is_master (struct mlx4_dev*) ; 
 scalar_t__ mlx4_is_slave (struct mlx4_dev*) ; 
 scalar_t__ mlx4_low_memory_profile () ; 
 int mlx4_make_profile (struct mlx4_dev*,struct mlx4_profile*,struct mlx4_dev_cap*,struct mlx4_init_hca_param*) ; 
 int /*<<< orphan*/  mlx4_parav_master_pf_caps (struct mlx4_dev*) ; 
 struct mlx4_priv* mlx4_priv (struct mlx4_dev*) ; 
 int mlx4_query_func (struct mlx4_dev*,struct mlx4_dev_cap*) ; 
 int /*<<< orphan*/  mlx4_set_port_mask (struct mlx4_dev*) ; 
 int mlx4_slave_cap (struct mlx4_dev*) ; 
 int /*<<< orphan*/  mlx4_slave_exit (struct mlx4_dev*) ; 
 scalar_t__ mlx4_validate_optimized_steering (struct mlx4_dev*) ; 
 int /*<<< orphan*/  mlx4_warn (struct mlx4_dev*,char*) ; 
 int /*<<< orphan*/  unmap_bf_area (struct mlx4_dev*) ; 
 int /*<<< orphan*/  unmap_internal_clock (struct mlx4_dev*) ; 

__attribute__((used)) static int mlx4_init_hca(struct mlx4_dev *dev)
{
	struct mlx4_priv	  *priv = mlx4_priv(dev);
	struct mlx4_adapter	   adapter;
	struct mlx4_dev_cap	   dev_cap = {};
	struct mlx4_profile	   profile;
	struct mlx4_init_hca_param init_hca;
	u64 icm_size;
	struct mlx4_config_dev_params params;
	int err;

	if (!mlx4_is_slave(dev)) {
		err = mlx4_dev_cap(dev, &dev_cap);
		if (err) {
			mlx4_err(dev, "QUERY_DEV_CAP command failed, aborting\n");
			return err;
		}

		choose_steering_mode(dev, &dev_cap);
		choose_tunnel_offload_mode(dev, &dev_cap);

		if (dev->caps.dmfs_high_steer_mode == MLX4_STEERING_DMFS_A0_STATIC &&
		    mlx4_is_master(dev))
			dev->caps.function_caps |= MLX4_FUNC_CAP_DMFS_A0_STATIC;

		err = mlx4_get_phys_port_id(dev);
		if (err)
			mlx4_err(dev, "Fail to get physical port id\n");

		if (mlx4_is_master(dev))
			mlx4_parav_master_pf_caps(dev);

		if (mlx4_low_memory_profile()) {
			mlx4_info(dev, "Running from within kdump kernel. Using low memory profile\n");
			profile = low_mem_profile;
		} else {
			profile = default_profile;
		}
		if (dev->caps.steering_mode ==
		    MLX4_STEERING_MODE_DEVICE_MANAGED)
			profile.num_mcg = MLX4_FS_NUM_MCG;

		icm_size = mlx4_make_profile(dev, &profile, &dev_cap,
					     &init_hca);
		if ((long long) icm_size < 0) {
			err = icm_size;
			return err;
		}

		dev->caps.max_fmr_maps = (1 << (32 - ilog2(dev->caps.num_mpts))) - 1;

		if (enable_4k_uar) {
			init_hca.log_uar_sz = ilog2(dev->caps.num_uars) +
						    PAGE_SHIFT - DEFAULT_UAR_PAGE_SHIFT;
			init_hca.uar_page_sz = DEFAULT_UAR_PAGE_SHIFT - 12;
		} else {
			init_hca.log_uar_sz = ilog2(dev->caps.num_uars);
			init_hca.uar_page_sz = PAGE_SHIFT - 12;
		}

		init_hca.mw_enabled = 0;
		if (dev->caps.flags & MLX4_DEV_CAP_FLAG_MEM_WINDOW ||
		    dev->caps.bmme_flags & MLX4_BMME_FLAG_TYPE_2_WIN)
			init_hca.mw_enabled = INIT_HCA_TPT_MW_ENABLE;

		err = mlx4_init_icm(dev, &dev_cap, &init_hca, icm_size);
		if (err)
			return err;

		err = mlx4_INIT_HCA(dev, &init_hca);
		if (err) {
			mlx4_err(dev, "INIT_HCA command failed, aborting\n");
			goto err_free_icm;
		}

		if (dev_cap.flags2 & MLX4_DEV_CAP_FLAG2_SYS_EQS) {
			err = mlx4_query_func(dev, &dev_cap);
			if (err < 0) {
				mlx4_err(dev, "QUERY_FUNC command failed, aborting.\n");
				goto err_close;
			} else if (err & MLX4_QUERY_FUNC_NUM_SYS_EQS) {
				dev->caps.num_eqs = dev_cap.max_eqs;
				dev->caps.reserved_eqs = dev_cap.reserved_eqs;
				dev->caps.reserved_uars = dev_cap.reserved_uars;
			}
		}

		/*
		 * If TS is supported by FW
		 * read HCA frequency by QUERY_HCA command
		 */
		if (dev->caps.flags2 & MLX4_DEV_CAP_FLAG2_TS) {
			memset(&init_hca, 0, sizeof(init_hca));
			err = mlx4_QUERY_HCA(dev, &init_hca);
			if (err) {
				mlx4_err(dev, "QUERY_HCA command failed, disable timestamp\n");
				dev->caps.flags2 &= ~MLX4_DEV_CAP_FLAG2_TS;
			} else {
				dev->caps.hca_core_clock =
					init_hca.hca_core_clock;
			}

			/* In case we got HCA frequency 0 - disable timestamping
			 * to avoid dividing by zero
			 */
			if (!dev->caps.hca_core_clock) {
				dev->caps.flags2 &= ~MLX4_DEV_CAP_FLAG2_TS;
				mlx4_err(dev,
					 "HCA frequency is 0 - timestamping is not supported\n");
			} else if (map_internal_clock(dev)) {
				/*
				 * Map internal clock,
				 * in case of failure disable timestamping
				 */
				dev->caps.flags2 &= ~MLX4_DEV_CAP_FLAG2_TS;
				mlx4_err(dev, "Failed to map internal clock. Timestamping is not supported\n");
			}
		}

		if (dev->caps.dmfs_high_steer_mode !=
		    MLX4_STEERING_DMFS_A0_NOT_SUPPORTED) {
			if (mlx4_validate_optimized_steering(dev))
				mlx4_warn(dev, "Optimized steering validation failed\n");

			if (dev->caps.dmfs_high_steer_mode ==
			    MLX4_STEERING_DMFS_A0_DISABLE) {
				dev->caps.dmfs_high_rate_qpn_base =
					dev->caps.reserved_qps_cnt[MLX4_QP_REGION_FW];
				dev->caps.dmfs_high_rate_qpn_range =
					MLX4_A0_STEERING_TABLE_SIZE;
			}

			mlx4_dbg(dev, "DMFS high rate steer mode is: %s\n",
				 dmfs_high_rate_steering_mode_str(
					dev->caps.dmfs_high_steer_mode));
		}
	} else {
		err = mlx4_init_slave(dev);
		if (err) {
			if (err != -EAGAIN)
				mlx4_err(dev, "Failed to initialize slave\n");
			return err;
		}

		err = mlx4_slave_cap(dev);
		if (err) {
			mlx4_err(dev, "Failed to obtain slave caps\n");
			goto err_close;
		}
	}

	if (map_bf_area(dev))
		mlx4_dbg(dev, "Failed to map blue flame area\n");

	/*Only the master set the ports, all the rest got it from it.*/
	if (!mlx4_is_slave(dev))
		mlx4_set_port_mask(dev);

	err = mlx4_QUERY_ADAPTER(dev, &adapter);
	if (err) {
		mlx4_err(dev, "QUERY_ADAPTER command failed, aborting\n");
		goto unmap_bf;
	}

	/* Query CONFIG_DEV parameters */
	err = mlx4_config_dev_retrieval(dev, &params);
	if (err && err != -ENOTSUPP) {
		mlx4_err(dev, "Failed to query CONFIG_DEV parameters\n");
	} else if (!err) {
		dev->caps.rx_checksum_flags_port[1] = params.rx_csum_flags_port_1;
		dev->caps.rx_checksum_flags_port[2] = params.rx_csum_flags_port_2;
	}
	priv->eq_table.inta_pin = adapter.inta_pin;
	memcpy(dev->board_id, adapter.board_id, sizeof dev->board_id);

	return 0;

unmap_bf:
	unmap_internal_clock(dev);
	unmap_bf_area(dev);

	if (mlx4_is_slave(dev)) {
		kfree(dev->caps.qp0_qkey);
		kfree(dev->caps.qp0_tunnel);
		kfree(dev->caps.qp0_proxy);
		kfree(dev->caps.qp1_tunnel);
		kfree(dev->caps.qp1_proxy);
	}

err_close:
	if (mlx4_is_slave(dev))
		mlx4_slave_exit(dev);
	else
		mlx4_CLOSE_HCA(dev, 0);

err_free_icm:
	if (!mlx4_is_slave(dev))
		mlx4_free_icms(dev);

	return err;
}