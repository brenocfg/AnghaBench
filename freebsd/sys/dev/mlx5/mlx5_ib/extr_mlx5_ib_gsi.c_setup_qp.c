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
typedef  size_t u16 ;
struct mlx5_ib_gsi_qp {int /*<<< orphan*/  lock; struct ib_qp** tx_qps; int /*<<< orphan*/  port_num; TYPE_1__* rx_qp; } ;
struct mlx5_ib_dev {int dummy; } ;
struct ib_qp {int dummy; } ;
struct ib_device {int dummy; } ;
struct TYPE_2__ {struct ib_device* device; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct ib_qp*) ; 
 int /*<<< orphan*/  PTR_ERR (struct ib_qp*) ; 
 int /*<<< orphan*/  WARN_ON_ONCE (struct ib_qp*) ; 
 struct ib_qp* create_gsi_ud_qp (struct mlx5_ib_gsi_qp*) ; 
 int ib_query_pkey (struct ib_device*,int /*<<< orphan*/ ,size_t,size_t*) ; 
 int /*<<< orphan*/  mlx5_ib_dbg (struct mlx5_ib_dev*,char*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  mlx5_ib_warn (struct mlx5_ib_dev*,char*,int /*<<< orphan*/ ,...) ; 
 int modify_to_rts (struct mlx5_ib_gsi_qp*,struct ib_qp*,size_t) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct mlx5_ib_dev* to_mdev (struct ib_device*) ; 

__attribute__((used)) static void setup_qp(struct mlx5_ib_gsi_qp *gsi, u16 qp_index)
{
	struct ib_device *device = gsi->rx_qp->device;
	struct mlx5_ib_dev *dev = to_mdev(device);
	struct ib_qp *qp;
	unsigned long flags;
	u16 pkey;
	int ret;

	ret = ib_query_pkey(device, gsi->port_num, qp_index, &pkey);
	if (ret) {
		mlx5_ib_warn(dev, "unable to read P_Key at port %d, index %d\n",
			     gsi->port_num, qp_index);
		return;
	}

	if (!pkey) {
		mlx5_ib_dbg(dev, "invalid P_Key at port %d, index %d.  Skipping.\n",
			    gsi->port_num, qp_index);
		return;
	}

	spin_lock_irqsave(&gsi->lock, flags);
	qp = gsi->tx_qps[qp_index];
	spin_unlock_irqrestore(&gsi->lock, flags);
	if (qp) {
		mlx5_ib_dbg(dev, "already existing GSI TX QP at port %d, index %d. Skipping\n",
			    gsi->port_num, qp_index);
		return;
	}

	qp = create_gsi_ud_qp(gsi);
	if (IS_ERR(qp)) {
		mlx5_ib_warn(dev, "unable to create hardware UD QP for GSI: %ld\n",
			     PTR_ERR(qp));
		return;
	}

	ret = modify_to_rts(gsi, qp, qp_index);
	if (ret)
		goto err_destroy_qp;

	spin_lock_irqsave(&gsi->lock, flags);
	WARN_ON_ONCE(gsi->tx_qps[qp_index]);
	gsi->tx_qps[qp_index] = qp;
	spin_unlock_irqrestore(&gsi->lock, flags);

	return;

err_destroy_qp:
	WARN_ON_ONCE(qp);
}