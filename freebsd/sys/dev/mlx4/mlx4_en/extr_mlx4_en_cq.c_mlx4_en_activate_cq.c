#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_8__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;
typedef  struct TYPE_11__   TYPE_10__ ;

/* Type definitions */
struct mlx4_en_priv {size_t port; int rx_ring_num; TYPE_1__** rx_ring; struct mlx4_en_cq** rx_cq; struct mlx4_en_dev* mdev; } ;
struct mlx4_en_dev {TYPE_5__* dev; int /*<<< orphan*/  priv_uar; int /*<<< orphan*/ * pndev; } ;
struct TYPE_11__ {unsigned long data; int /*<<< orphan*/  function; } ;
struct TYPE_17__ {int /*<<< orphan*/  event; int /*<<< orphan*/  comp; scalar_t__* arm_db; scalar_t__* set_ci_db; } ;
struct TYPE_13__ {int /*<<< orphan*/  dma; scalar_t__* db; } ;
struct TYPE_14__ {TYPE_2__ db; int /*<<< orphan*/  mtt; } ;
struct mlx4_en_cq {scalar_t__ is_tx; int vector; size_t ring; TYPE_10__ timer; TYPE_8__ mcq; TYPE_3__ wqres; int /*<<< orphan*/  size; int /*<<< orphan*/  buf_size; int /*<<< orphan*/  buf; int /*<<< orphan*/  dev; } ;
struct TYPE_15__ {int num_comp_vectors; } ;
struct TYPE_16__ {TYPE_4__ caps; } ;
struct TYPE_12__ {int /*<<< orphan*/  actual_size; } ;

/* Variables and functions */
 scalar_t__ RX ; 
 int /*<<< orphan*/  init_timer (TYPE_10__*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mlx4_assign_eq (TYPE_5__*,size_t,int*) ; 
 int mlx4_cq_alloc (TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_8__*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mlx4_en_cq_event ; 
 int /*<<< orphan*/  mlx4_en_poll_tx_cq ; 
 int /*<<< orphan*/  mlx4_en_rx_irq ; 
 int /*<<< orphan*/  mlx4_en_tx_irq ; 
 int /*<<< orphan*/  mlx4_err (struct mlx4_en_dev*,char*,int) ; 
 int /*<<< orphan*/  mlx4_is_eq_vector_valid (TYPE_5__*,size_t,int) ; 
 int /*<<< orphan*/  mlx4_release_eq (TYPE_5__*,int) ; 

int mlx4_en_activate_cq(struct mlx4_en_priv *priv, struct mlx4_en_cq *cq,
			int cq_idx)
{
	struct mlx4_en_dev *mdev = priv->mdev;
	int err = 0;
	int timestamp_en = 0;
	bool assigned_eq = false;

	cq->dev = mdev->pndev[priv->port];
	cq->mcq.set_ci_db  = cq->wqres.db.db;
	cq->mcq.arm_db     = cq->wqres.db.db + 1;
	*cq->mcq.set_ci_db = 0;
	*cq->mcq.arm_db    = 0;
	memset(cq->buf, 0, cq->buf_size);

	if (cq->is_tx == RX) {
		if (!mlx4_is_eq_vector_valid(mdev->dev, priv->port,
					     cq->vector)) {
			cq->vector = cq_idx % mdev->dev->caps.num_comp_vectors;

			err = mlx4_assign_eq(mdev->dev, priv->port,
					     &cq->vector);
			if (err) {
				mlx4_err(mdev, "Failed assigning an EQ to CQ vector %d\n",
					 cq->vector);
				goto free_eq;
			}

			assigned_eq = true;
		}
	} else {
		struct mlx4_en_cq *rx_cq;
		/*
		 * For TX we use the same irq per
		 * ring we assigned for the RX
		 */
		cq_idx = cq_idx % priv->rx_ring_num;
		rx_cq = priv->rx_cq[cq_idx];
		cq->vector = rx_cq->vector;
	}

	if (!cq->is_tx)
		cq->size = priv->rx_ring[cq->ring]->actual_size;

	err = mlx4_cq_alloc(mdev->dev, cq->size, &cq->wqres.mtt,
			    &mdev->priv_uar, cq->wqres.db.dma, &cq->mcq,
			    cq->vector, 0, timestamp_en);
	if (err)
		goto free_eq;

	cq->mcq.comp  = cq->is_tx ? mlx4_en_tx_irq : mlx4_en_rx_irq;
	cq->mcq.event = mlx4_en_cq_event;

        if (cq->is_tx) {
                init_timer(&cq->timer);
                cq->timer.function = mlx4_en_poll_tx_cq;
                cq->timer.data = (unsigned long) cq;
        }


	return 0;

free_eq:
	if (assigned_eq)
		mlx4_release_eq(mdev->dev, cq->vector);
	cq->vector = mdev->dev->caps.num_comp_vectors;
	return err;
}