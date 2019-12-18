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
struct TYPE_7__ {int /*<<< orphan*/  wrid; } ;
struct TYPE_10__ {int /*<<< orphan*/  wr_data; int /*<<< orphan*/  wrid; int /*<<< orphan*/  w_list; int /*<<< orphan*/  wqe_head; } ;
struct mlx5_ib_qp {TYPE_3__* bf; int /*<<< orphan*/  buf; TYPE_1__ rq; TYPE_4__ sq; int /*<<< orphan*/  db; } ;
struct mlx5_ib_dev {TYPE_5__* mdev; } ;
struct TYPE_8__ {int /*<<< orphan*/  uuari; } ;
struct TYPE_11__ {TYPE_2__ priv; } ;
struct TYPE_9__ {int /*<<< orphan*/  uuarn; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_uuar (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5_buf_free (TYPE_5__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlx5_db_free (TYPE_5__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void destroy_qp_kernel(struct mlx5_ib_dev *dev, struct mlx5_ib_qp *qp)
{
	mlx5_db_free(dev->mdev, &qp->db);
	kfree(qp->sq.wqe_head);
	kfree(qp->sq.w_list);
	kfree(qp->sq.wrid);
	kfree(qp->sq.wr_data);
	kfree(qp->rq.wrid);
	mlx5_buf_free(dev->mdev, &qp->buf);
	free_uuar(&dev->mdev->priv.uuari, qp->bf->uuarn);
}