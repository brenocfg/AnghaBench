#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int qpn; } ;
struct TYPE_10__ {int /*<<< orphan*/  usr_page; } ;
struct TYPE_9__ {int /*<<< orphan*/  mtt; } ;
struct TYPE_8__ {TYPE_1__* uar; } ;
struct mlx4_en_tx_ring {int cqn; int cons; int last_nr_txbb; int doorbell_qpn; int /*<<< orphan*/  qp_state; TYPE_5__ qp; TYPE_4__ context; TYPE_3__ wqres; TYPE_2__ bf; scalar_t__ bf_enabled; int /*<<< orphan*/  qpn; int /*<<< orphan*/  stride; int /*<<< orphan*/  size; scalar_t__ watchdog_time; int /*<<< orphan*/  buf_size; int /*<<< orphan*/  buf; scalar_t__ poll_cnt; scalar_t__ prod; } ;
struct mlx4_en_priv {struct mlx4_en_dev* mdev; } ;
struct mlx4_en_dev {int /*<<< orphan*/  dev; } ;
struct TYPE_7__ {int /*<<< orphan*/  index; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLX4_QP_STATE_RST ; 
 int /*<<< orphan*/  cpu_to_be32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx4_en_fill_qp_context (struct mlx4_en_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,TYPE_4__*) ; 
 int mlx4_qp_to_ready (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_4__*,TYPE_5__*,int /*<<< orphan*/ *) ; 

int mlx4_en_activate_tx_ring(struct mlx4_en_priv *priv,
			     struct mlx4_en_tx_ring *ring,
			     int cq, int user_prio)
{
	struct mlx4_en_dev *mdev = priv->mdev;
	int err;

	ring->cqn = cq;
	ring->prod = 0;
	ring->cons = 0xffffffff;
	ring->last_nr_txbb = 1;
	ring->poll_cnt = 0;
	memset(ring->buf, 0, ring->buf_size);
	ring->watchdog_time = 0;

	ring->qp_state = MLX4_QP_STATE_RST;
	ring->doorbell_qpn = ring->qp.qpn << 8;

	mlx4_en_fill_qp_context(priv, ring->size, ring->stride, 1, 0, ring->qpn,
				ring->cqn, user_prio, &ring->context);
	if (ring->bf_enabled)
		ring->context.usr_page = cpu_to_be32(ring->bf.uar->index);

	err = mlx4_qp_to_ready(mdev->dev, &ring->wqres.mtt, &ring->context,
			       &ring->qp, &ring->qp_state);
	return err;
}