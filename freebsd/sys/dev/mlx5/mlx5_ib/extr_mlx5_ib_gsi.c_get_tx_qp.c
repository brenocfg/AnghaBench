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
struct mlx5_ib_gsi_qp {int num_qps; struct ib_qp** tx_qps; struct ib_qp* rx_qp; } ;
struct mlx5_ib_dev {int dummy; } ;
struct ib_ud_wr {int pkey_index; } ;
struct ib_qp {int /*<<< orphan*/  device; } ;

/* Variables and functions */
 int /*<<< orphan*/  mlx5_ib_deth_sqpn_cap (struct mlx5_ib_dev*) ; 
 struct mlx5_ib_dev* to_mdev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct ib_qp *get_tx_qp(struct mlx5_ib_gsi_qp *gsi, struct ib_ud_wr *wr)
{
	struct mlx5_ib_dev *dev = to_mdev(gsi->rx_qp->device);
	int qp_index = wr->pkey_index;

	if (!mlx5_ib_deth_sqpn_cap(dev))
		return gsi->rx_qp;

	if (qp_index >= gsi->num_qps)
		return NULL;

	return gsi->tx_qps[qp_index];
}