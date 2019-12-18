#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
typedef  TYPE_1__* u16 ;
struct mlx5_core_dev {int dummy; } ;
struct TYPE_9__ {int /*<<< orphan*/  counter_id; } ;
struct TYPE_8__ {int /*<<< orphan*/  counter_id; } ;

/* Variables and functions */
 int ENOMEM ; 
 void* MLX5_ADDR_OF (TYPE_2__*,void*,int /*<<< orphan*/ ) ; 
 TYPE_1__* MLX5_CAP_DEBUG (struct mlx5_core_dev*,int /*<<< orphan*/ ) ; 
 int MLX5_CAP_GEN (struct mlx5_core_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MLX5_CORE_GENERAL_DIAGNOSTICS_NUM ; 
 int /*<<< orphan*/  MLX5_CORE_PCI_DIAGNOSTICS_NUM ; 
 int /*<<< orphan*/  MLX5_SET (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,...) ; 
 int MLX5_ST_SZ_BYTES (TYPE_2__*) ; 
 int /*<<< orphan*/  debug ; 
 TYPE_2__* diagnostic_counter ; 
 int /*<<< orphan*/  diagnostic_params_context ; 
 int /*<<< orphan*/  diagnostic_params_ctx ; 
 int /*<<< orphan*/  enable ; 
 int /*<<< orphan*/  kvfree (void*) ; 
 int /*<<< orphan*/  mlx5_core_general_diagnostics_table ; 
 int mlx5_core_get_index_of_diag_counter (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  mlx5_core_pci_diagnostics_table ; 
 int mlx5_set_diagnostic_params (struct mlx5_core_dev*,void*,int) ; 
 void* mlx5_vzalloc (int) ; 
 int /*<<< orphan*/  num_of_counters ; 
 int /*<<< orphan*/  num_of_diagnostic_counters ; 
 int /*<<< orphan*/  on_demand ; 
 TYPE_2__* set_diagnostic_params_in ; 
 int /*<<< orphan*/  single ; 

int mlx5_core_set_diagnostics_full(struct mlx5_core_dev *dev,
				   u8 enable_pci, u8 enable_general)
{
	void *diag_params_ctx;
	void *in;
	int numcounters;
	int inlen;
	int err;
	int x;
	int y;

	if (MLX5_CAP_GEN(dev, debug) == 0)
		return 0;

	numcounters = MLX5_CAP_GEN(dev, num_of_diagnostic_counters);
	if (numcounters == 0)
		return 0;

	inlen = MLX5_ST_SZ_BYTES(set_diagnostic_params_in) +
	    MLX5_ST_SZ_BYTES(diagnostic_counter) * numcounters;
	in = mlx5_vzalloc(inlen);
	if (in == NULL)
		return -ENOMEM;

	diag_params_ctx = MLX5_ADDR_OF(set_diagnostic_params_in, in,
				       diagnostic_params_ctx);

	MLX5_SET(diagnostic_params_context, diag_params_ctx,
		 enable, enable_pci || enable_general);
	MLX5_SET(diagnostic_params_context, diag_params_ctx,
		 single, 1);
	MLX5_SET(diagnostic_params_context, diag_params_ctx,
		 on_demand, 1);

	/* collect the counters we want to enable */
	for (x = y = 0; x != numcounters; x++) {
		u16 counter_id =
			MLX5_CAP_DEBUG(dev, diagnostic_counter[x].counter_id);
		int index = -1;

		if (index < 0 && enable_pci != 0) {
			/* check if counter ID exists in local table */
			index = mlx5_core_get_index_of_diag_counter(
			    mlx5_core_pci_diagnostics_table,
			    MLX5_CORE_PCI_DIAGNOSTICS_NUM,
			    counter_id);
		}
		if (index < 0 && enable_general != 0) {
			/* check if counter ID exists in local table */
			index = mlx5_core_get_index_of_diag_counter(
			    mlx5_core_general_diagnostics_table,
			    MLX5_CORE_GENERAL_DIAGNOSTICS_NUM,
			    counter_id);
		}
		if (index < 0)
			continue;

		MLX5_SET(diagnostic_params_context,
			 diag_params_ctx,
			 counter_id[y].counter_id,
			 counter_id);
		y++;
	}

	/* recompute input length */
	inlen = MLX5_ST_SZ_BYTES(set_diagnostic_params_in) +
	    MLX5_ST_SZ_BYTES(diagnostic_counter) * y;

	/* set number of counters */
	MLX5_SET(diagnostic_params_context, diag_params_ctx,
		 num_of_counters, y);

	/* execute firmware command */
	err = mlx5_set_diagnostic_params(dev, in, inlen);

	kvfree(in);

	return err;
}