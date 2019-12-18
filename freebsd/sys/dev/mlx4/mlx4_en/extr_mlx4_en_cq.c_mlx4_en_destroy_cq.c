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
struct mlx4_en_priv {struct mlx4_en_dev* mdev; int /*<<< orphan*/  port; } ;
struct mlx4_en_dev {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  buf; } ;
struct mlx4_en_cq {scalar_t__ is_tx; int /*<<< orphan*/ * buf; scalar_t__ buf_size; scalar_t__ vector; TYPE_1__ wqres; int /*<<< orphan*/  tq; int /*<<< orphan*/  cq_task; } ;

/* Variables and functions */
 scalar_t__ RX ; 
 int /*<<< orphan*/  kfree (struct mlx4_en_cq*) ; 
 int /*<<< orphan*/  mlx4_en_unmap_buffer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlx4_free_hwq_res (int /*<<< orphan*/ ,TYPE_1__*,scalar_t__) ; 
 scalar_t__ mlx4_is_eq_vector_valid (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  mlx4_release_eq (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  taskqueue_drain (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  taskqueue_free (int /*<<< orphan*/ ) ; 

void mlx4_en_destroy_cq(struct mlx4_en_priv *priv, struct mlx4_en_cq **pcq)
{
	struct mlx4_en_dev *mdev = priv->mdev;
	struct mlx4_en_cq *cq = *pcq;

	taskqueue_drain(cq->tq, &cq->cq_task);
	taskqueue_free(cq->tq);
	mlx4_en_unmap_buffer(&cq->wqres.buf);
	mlx4_free_hwq_res(mdev->dev, &cq->wqres, cq->buf_size);
	if (mlx4_is_eq_vector_valid(mdev->dev, priv->port, cq->vector) &&
	    cq->is_tx == RX)
		mlx4_release_eq(priv->mdev->dev, cq->vector);
	cq->vector = 0;
	cq->buf_size = 0;
	cq->buf = NULL;
	kfree(cq);
	*pcq = NULL;
}