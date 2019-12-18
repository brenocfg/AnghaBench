#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/ * done; } ;
struct ib_wc {int /*<<< orphan*/  wr_id; int /*<<< orphan*/  pkey_index; } ;
struct mlx5_ib_gsi_wr {int completed; TYPE_4__ cqe; struct ib_wc wc; } ;
struct TYPE_6__ {size_t max_send_wr; } ;
struct mlx5_ib_gsi_qp {size_t outstanding_pi; size_t outstanding_ci; TYPE_2__ cap; struct mlx5_ib_gsi_wr* outstanding_wrs; TYPE_1__* rx_qp; } ;
struct mlx5_ib_dev {int dummy; } ;
struct TYPE_7__ {TYPE_4__* wr_cqe; int /*<<< orphan*/  wr_id; } ;
struct ib_ud_wr {TYPE_3__ wr; int /*<<< orphan*/  pkey_index; } ;
struct TYPE_5__ {int /*<<< orphan*/  device; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  handle_single_completion ; 
 int /*<<< orphan*/  memset (struct ib_wc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mlx5_ib_warn (struct mlx5_ib_dev*,char*) ; 
 struct mlx5_ib_dev* to_mdev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mlx5_ib_add_outstanding_wr(struct mlx5_ib_gsi_qp *gsi,
				      struct ib_ud_wr *wr, struct ib_wc *wc)
{
	struct mlx5_ib_dev *dev = to_mdev(gsi->rx_qp->device);
	struct mlx5_ib_gsi_wr *gsi_wr;

	if (gsi->outstanding_pi == gsi->outstanding_ci + gsi->cap.max_send_wr) {
		mlx5_ib_warn(dev, "no available GSI work request.\n");
		return -ENOMEM;
	}

	gsi_wr = &gsi->outstanding_wrs[gsi->outstanding_pi %
				       gsi->cap.max_send_wr];
	gsi->outstanding_pi++;

	if (!wc) {
		memset(&gsi_wr->wc, 0, sizeof(gsi_wr->wc));
		gsi_wr->wc.pkey_index = wr->pkey_index;
		gsi_wr->wc.wr_id = wr->wr.wr_id;
	} else {
		gsi_wr->wc = *wc;
		gsi_wr->completed = true;
	}

	gsi_wr->cqe.done = &handle_single_completion;
	wr->wr.wr_cqe = &gsi_wr->cqe;

	return 0;
}