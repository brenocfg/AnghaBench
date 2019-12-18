#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
struct TYPE_2__ {int tx_queue_size; int tx_completion_fact_max; int tx_completion_fact; } ;
struct mlx5e_priv {TYPE_1__ params_ethtool; } ;

/* Variables and functions */
 int MLX5_SEND_WQE_MAX_WQEBBS ; 

__attribute__((used)) static void
mlx5e_ethtool_sync_tx_completion_fact(struct mlx5e_priv *priv)
{
	/*
	 * Limit the maximum distance between completion events to
	 * half of the currently set TX queue size.
	 *
	 * The maximum number of queue entries a single IP packet can
	 * consume is given by MLX5_SEND_WQE_MAX_WQEBBS.
	 *
	 * The worst case max value is then given as below:
	 */
	uint64_t max = priv->params_ethtool.tx_queue_size /
	    (2 * MLX5_SEND_WQE_MAX_WQEBBS);

	/*
	 * Update the maximum completion factor value in case the
	 * tx_queue_size field changed. Ensure we don't overflow
	 * 16-bits.
	 */
	if (max < 1)
		max = 1;
	else if (max > 65535)
		max = 65535;
	priv->params_ethtool.tx_completion_fact_max = max;

	/*
	 * Verify that the current TX completion factor is within the
	 * given limits:
	 */
	if (priv->params_ethtool.tx_completion_fact < 1)
		priv->params_ethtool.tx_completion_fact = 1;
	else if (priv->params_ethtool.tx_completion_fact > max)
		priv->params_ethtool.tx_completion_fact = max;
}