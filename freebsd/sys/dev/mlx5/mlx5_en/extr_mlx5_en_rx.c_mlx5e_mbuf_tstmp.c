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
typedef  int uint64_t ;
typedef  scalar_t__ u_int ;
struct mlx5e_priv {size_t clbr_curr; struct mlx5e_clbr_point* clbr_points; } ;
struct mlx5e_clbr_point {scalar_t__ clbr_gen; int clbr_hw_prev; int base_curr; int base_prev; int clbr_hw_curr; } ;

/* Variables and functions */
 int MLX5E_TSTMP_PREC ; 
 scalar_t__ atomic_load_acq_int (scalar_t__*) ; 
 int /*<<< orphan*/  atomic_thread_fence_acq () ; 

__attribute__((used)) static uint64_t
mlx5e_mbuf_tstmp(struct mlx5e_priv *priv, uint64_t hw_tstmp)
{
	struct mlx5e_clbr_point *cp, dcp;
	uint64_t a1, a2, res;
	u_int gen;

	do {
		cp = &priv->clbr_points[priv->clbr_curr];
		gen = atomic_load_acq_int(&cp->clbr_gen);
		if (gen == 0)
			return (0);
		dcp = *cp;
		atomic_thread_fence_acq();
	} while (gen != cp->clbr_gen);

	a1 = (hw_tstmp - dcp.clbr_hw_prev) >> MLX5E_TSTMP_PREC;
	a2 = (dcp.base_curr - dcp.base_prev) >> MLX5E_TSTMP_PREC;
	res = (a1 * a2) << MLX5E_TSTMP_PREC;

	/*
	 * Divisor cannot be zero because calibration callback
	 * checks for the condition and disables timestamping
	 * if clock halted.
	 */
	res /= (dcp.clbr_hw_curr - dcp.clbr_hw_prev) >> MLX5E_TSTMP_PREC;

	res += dcp.base_prev;
	return (res);
}