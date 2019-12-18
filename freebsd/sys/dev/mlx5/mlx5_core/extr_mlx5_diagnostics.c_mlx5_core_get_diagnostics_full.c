#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {void* tx_pci_fatal_errors; void* tx_pci_non_fatal_errors; void* tx_pci_errors; void* rx_pci_errors; } ;
union mlx5_core_pci_diagnostics {TYPE_1__ counter; int /*<<< orphan*/  array; } ;
union mlx5_core_general_diagnostics {int /*<<< orphan*/  array; } ;
typedef  int /*<<< orphan*/  u64 ;
typedef  void* u16 ;
struct mlx5_core_dev {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  pcie_timers_states; int /*<<< orphan*/  pcie_perf_counters; } ;
struct TYPE_5__ {int /*<<< orphan*/  counter_value_h; int /*<<< orphan*/  counter_id; } ;

/* Variables and functions */
 int ENOMEM ; 
 void* MLX5_ADDR_OF (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 
 int MLX5_CAP_GEN (struct mlx5_core_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MLX5_CORE_GENERAL_DIAGNOSTICS_NUM ; 
 int /*<<< orphan*/  MLX5_CORE_PCI_DIAGNOSTICS_NUM ; 
 void* MLX5_GET (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MLX5_GET64 (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MLX5_PCIE_PERFORMANCE_COUNTERS_GROUP ; 
 int /*<<< orphan*/  MLX5_PCIE_TIMERS_AND_STATES_COUNTERS_GROUP ; 
 int /*<<< orphan*/  MLX5_REG_MPCNT ; 
 int /*<<< orphan*/  MLX5_SET (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int MLX5_ST_SZ_BYTES (int /*<<< orphan*/ ) ; 
 TYPE_3__ counter_set ; 
 int /*<<< orphan*/  debug ; 
 TYPE_2__* diag_counter ; 
 int /*<<< orphan*/  diagnostic_counter ; 
 int /*<<< orphan*/  fatal_err_msg_sent ; 
 int /*<<< orphan*/  grp ; 
 int /*<<< orphan*/  kvfree (void*) ; 
 int mlx5_core_access_reg (struct mlx5_core_dev*,void*,int,void*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5_core_general_diagnostics_table ; 
 int /*<<< orphan*/  mlx5_core_pci_diagnostics_table ; 
 int /*<<< orphan*/  mlx5_core_put_diag_counter (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 
 int mlx5_query_diagnostic_counters (struct mlx5_core_dev*,int,int /*<<< orphan*/ ,void*,int) ; 
 void* mlx5_vzalloc (int) ; 
 int /*<<< orphan*/  mpcnt_reg ; 
 int /*<<< orphan*/  non_fatal_err_msg_sent ; 
 int /*<<< orphan*/  num_of_diagnostic_counters ; 
 int /*<<< orphan*/  pcie_perf_counters ; 
 int /*<<< orphan*/  pcie_timers_states ; 
 int /*<<< orphan*/  query_diagnostic_counters_out ; 
 int /*<<< orphan*/  rx_errors ; 
 int /*<<< orphan*/  tx_errors ; 

int mlx5_core_get_diagnostics_full(struct mlx5_core_dev *dev,
				   union mlx5_core_pci_diagnostics *pdiag,
				   union mlx5_core_general_diagnostics *pgen)
{
	void *out;
	void *in;
	int numcounters;
	int outlen;
	int inlen;
	int err;
	int x;

	if (MLX5_CAP_GEN(dev, debug) == 0)
		return 0;

	numcounters = MLX5_CAP_GEN(dev, num_of_diagnostic_counters);
	if (numcounters == 0)
		return 0;

	outlen = MLX5_ST_SZ_BYTES(query_diagnostic_counters_out) +
	    MLX5_ST_SZ_BYTES(diagnostic_counter) * numcounters;

	out = mlx5_vzalloc(outlen);
	if (out == NULL)
		return -ENOMEM;

	err = mlx5_query_diagnostic_counters(dev, 1, 0, out, outlen);
	if (err == 0) {
		for (x = 0; x != numcounters; x++) {
			u16 counter_id = MLX5_GET(
			    query_diagnostic_counters_out,
			    out, diag_counter[x].counter_id);
			u64 counter_value = MLX5_GET64(
			    query_diagnostic_counters_out,
			    out, diag_counter[x].counter_value_h);

			if (pdiag != NULL) {
				mlx5_core_put_diag_counter(
				    mlx5_core_pci_diagnostics_table,
				    pdiag->array,
				    MLX5_CORE_PCI_DIAGNOSTICS_NUM,
				    counter_id, counter_value);
			}
			if (pgen != NULL) {
				mlx5_core_put_diag_counter(
				    mlx5_core_general_diagnostics_table,
				    pgen->array,
				    MLX5_CORE_GENERAL_DIAGNOSTICS_NUM,
				    counter_id, counter_value);
			}
		}
	}
	kvfree(out);

	if (pdiag != NULL) {
		inlen = MLX5_ST_SZ_BYTES(mpcnt_reg);
		outlen = MLX5_ST_SZ_BYTES(mpcnt_reg);

		in = mlx5_vzalloc(inlen);
		if (in == NULL)
			return -ENOMEM;

		out = mlx5_vzalloc(outlen);
		if (out == NULL) {
			kvfree(in);
			return -ENOMEM;
		}
		MLX5_SET(mpcnt_reg, in, grp,
			 MLX5_PCIE_PERFORMANCE_COUNTERS_GROUP);

		err = mlx5_core_access_reg(dev, in, inlen, out, outlen,
					   MLX5_REG_MPCNT, 0, 0);
		if (err == 0) {
			void *pcounters = MLX5_ADDR_OF(mpcnt_reg, out,
			    counter_set.pcie_perf_counters);

			pdiag->counter.rx_pci_errors =
			    MLX5_GET(pcie_perf_counters,
				     pcounters, rx_errors);
			pdiag->counter.tx_pci_errors =
			    MLX5_GET(pcie_perf_counters,
				     pcounters, tx_errors);
		}
		MLX5_SET(mpcnt_reg, in, grp,
			 MLX5_PCIE_TIMERS_AND_STATES_COUNTERS_GROUP);

		err = mlx5_core_access_reg(dev, in, inlen, out, outlen,
		    MLX5_REG_MPCNT, 0, 0);
		if (err == 0) {
			void *pcounters = MLX5_ADDR_OF(mpcnt_reg, out,
			    counter_set.pcie_timers_states);

			pdiag->counter.tx_pci_non_fatal_errors =
			    MLX5_GET(pcie_timers_states,
				     pcounters, non_fatal_err_msg_sent);
			pdiag->counter.tx_pci_fatal_errors =
			    MLX5_GET(pcie_timers_states,
				     pcounters, fatal_err_msg_sent);
		}
		kvfree(in);
		kvfree(out);
	}
	return 0;
}