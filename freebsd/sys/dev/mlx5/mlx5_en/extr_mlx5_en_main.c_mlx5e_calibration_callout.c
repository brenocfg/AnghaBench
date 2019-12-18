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
struct timespec {int dummy; } ;
struct mlx5e_priv {size_t clbr_curr; scalar_t__ clbr_done; int /*<<< orphan*/  clbr_gen; int /*<<< orphan*/  ifp; struct mlx5e_clbr_point* clbr_points; } ;
struct mlx5e_clbr_point {int clbr_hw_prev; int clbr_hw_curr; scalar_t__ clbr_gen; int /*<<< orphan*/  base_curr; int /*<<< orphan*/  base_prev; } ;

/* Variables and functions */
 int MLX5E_TSTMP_PREC ; 
 int /*<<< orphan*/  atomic_store_rel_int (scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_thread_fence_rel () ; 
 int /*<<< orphan*/  mlx5_en_err (int /*<<< orphan*/ ,char*,int,int) ; 
 scalar_t__ mlx5e_calibration_duration ; 
 int mlx5e_hw_clock (struct mlx5e_priv*) ; 
 int /*<<< orphan*/  mlx5e_reset_calibration_callout (struct mlx5e_priv*) ; 
 int /*<<< orphan*/  mlx5e_timespec2usec (struct timespec*) ; 
 int /*<<< orphan*/  nanouptime (struct timespec*) ; 
 int nitems (struct mlx5e_clbr_point*) ; 

__attribute__((used)) static void
mlx5e_calibration_callout(void *arg)
{
	struct mlx5e_priv *priv;
	struct mlx5e_clbr_point *next, *curr;
	struct timespec ts;
	int clbr_curr_next;

	priv = arg;
	curr = &priv->clbr_points[priv->clbr_curr];
	clbr_curr_next = priv->clbr_curr + 1;
	if (clbr_curr_next >= nitems(priv->clbr_points))
		clbr_curr_next = 0;
	next = &priv->clbr_points[clbr_curr_next];

	next->base_prev = curr->base_curr;
	next->clbr_hw_prev = curr->clbr_hw_curr;

	next->clbr_hw_curr = mlx5e_hw_clock(priv);
	if (((next->clbr_hw_curr - curr->clbr_hw_curr) >> MLX5E_TSTMP_PREC) ==
	    0) {
		if (priv->clbr_done != 0) {
			mlx5_en_err(priv->ifp,
			    "HW failed tstmp frozen %#jx %#jx, disabling\n",
			     next->clbr_hw_curr, curr->clbr_hw_prev);
			priv->clbr_done = 0;
		}
		atomic_store_rel_int(&curr->clbr_gen, 0);
		return;
	}

	nanouptime(&ts);
	next->base_curr = mlx5e_timespec2usec(&ts);

	curr->clbr_gen = 0;
	atomic_thread_fence_rel();
	priv->clbr_curr = clbr_curr_next;
	atomic_store_rel_int(&next->clbr_gen, ++(priv->clbr_gen));

	if (priv->clbr_done < mlx5e_calibration_duration)
		priv->clbr_done++;
	mlx5e_reset_calibration_callout(priv);
}