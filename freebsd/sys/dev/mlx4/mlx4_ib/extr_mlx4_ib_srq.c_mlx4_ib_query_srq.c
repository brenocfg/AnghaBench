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
struct TYPE_2__ {int /*<<< orphan*/  max_gs; scalar_t__ max; } ;
struct mlx4_ib_srq {TYPE_1__ msrq; } ;
struct mlx4_ib_dev {int /*<<< orphan*/  dev; } ;
struct ib_srq_attr {int srq_limit; int /*<<< orphan*/  max_sge; scalar_t__ max_wr; } ;
struct ib_srq {int /*<<< orphan*/  device; } ;

/* Variables and functions */
 int mlx4_srq_query (int /*<<< orphan*/ ,TYPE_1__*,int*) ; 
 struct mlx4_ib_dev* to_mdev (int /*<<< orphan*/ ) ; 
 struct mlx4_ib_srq* to_msrq (struct ib_srq*) ; 

int mlx4_ib_query_srq(struct ib_srq *ibsrq, struct ib_srq_attr *srq_attr)
{
	struct mlx4_ib_dev *dev = to_mdev(ibsrq->device);
	struct mlx4_ib_srq *srq = to_msrq(ibsrq);
	int ret;
	int limit_watermark;

	ret = mlx4_srq_query(dev->dev, &srq->msrq, &limit_watermark);
	if (ret)
		return ret;

	srq_attr->srq_limit = limit_watermark;
	srq_attr->max_wr    = srq->msrq.max - 1;
	srq_attr->max_sge   = srq->msrq.max_gs;

	return 0;
}