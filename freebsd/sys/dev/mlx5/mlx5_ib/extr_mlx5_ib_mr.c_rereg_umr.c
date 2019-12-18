#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  void* u64 ;
struct umr_common {int /*<<< orphan*/  sem; int /*<<< orphan*/  qp; } ;
struct TYPE_9__ {int /*<<< orphan*/  send_flags; int /*<<< orphan*/ * wr_cqe; } ;
struct TYPE_7__ {void* virt_addr; } ;
struct mlx5_umr_wr {int access_flags; TYPE_4__ wr; struct ib_pd* pd; void* length; TYPE_2__ target; } ;
struct mlx5_ib_umr_context {int status; int /*<<< orphan*/  done; int /*<<< orphan*/  cqe; } ;
struct TYPE_8__ {int /*<<< orphan*/  key; } ;
struct mlx5_ib_mr {TYPE_3__ mmkey; int /*<<< orphan*/  umem; } ;
struct TYPE_6__ {struct device* dma_device; } ;
struct mlx5_ib_dev {struct umr_common umrc; TYPE_1__ ib_dev; } ;
struct ib_sge {int dummy; } ;
struct ib_send_wr {int dummy; } ;
struct ib_pd {int /*<<< orphan*/  device; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;
typedef  int /*<<< orphan*/  __be64 ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int EFAULT ; 
 int IB_MR_REREG_ACCESS ; 
 int IB_MR_REREG_PD ; 
 int IB_MR_REREG_TRANS ; 
 int IB_WC_SUCCESS ; 
 int /*<<< orphan*/  MLX5_IB_SEND_UMR_FAIL_IF_FREE ; 
 int /*<<< orphan*/  MLX5_IB_SEND_UMR_UPDATE_ACCESS ; 
 int /*<<< orphan*/  MLX5_IB_SEND_UMR_UPDATE_PD ; 
 int /*<<< orphan*/  MLX5_IB_SEND_UMR_UPDATE_TRANSLATION ; 
 int dma_map_mr_pas (struct mlx5_ib_dev*,int /*<<< orphan*/ ,int,int,int*,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dma_unmap_single (struct device*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  down (int /*<<< orphan*/ *) ; 
 int ib_post_send (int /*<<< orphan*/ ,TYPE_4__*,struct ib_send_wr**) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlx5_ib_init_umr_context (struct mlx5_ib_umr_context*) ; 
 int /*<<< orphan*/  mlx5_ib_warn (struct mlx5_ib_dev*,char*,int) ; 
 int /*<<< orphan*/  prep_umr_wqe_common (struct ib_pd*,TYPE_4__*,struct ib_sge*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 struct mlx5_ib_dev* to_mdev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  up (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int rereg_umr(struct ib_pd *pd, struct mlx5_ib_mr *mr, u64 virt_addr,
		     u64 length, int npages, int page_shift, int order,
		     int access_flags, int flags)
{
	struct mlx5_ib_dev *dev = to_mdev(pd->device);
	struct device *ddev = dev->ib_dev.dma_device;
	struct mlx5_ib_umr_context umr_context;
	struct ib_send_wr *bad;
	struct mlx5_umr_wr umrwr = {};
	struct ib_sge sg;
	struct umr_common *umrc = &dev->umrc;
	dma_addr_t dma = 0;
	__be64 *mr_pas = NULL;
	int size;
	int err;

	mlx5_ib_init_umr_context(&umr_context);

	umrwr.wr.wr_cqe = &umr_context.cqe;
	umrwr.wr.send_flags = MLX5_IB_SEND_UMR_FAIL_IF_FREE;

	if (flags & IB_MR_REREG_TRANS) {
		err = dma_map_mr_pas(dev, mr->umem, npages, page_shift, &size,
				     &mr_pas, &dma);
		if (err)
			return err;

		umrwr.target.virt_addr = virt_addr;
		umrwr.length = length;
		umrwr.wr.send_flags |= MLX5_IB_SEND_UMR_UPDATE_TRANSLATION;
	}

	prep_umr_wqe_common(pd, &umrwr.wr, &sg, dma, npages, mr->mmkey.key,
			    page_shift);

	if (flags & IB_MR_REREG_PD) {
		umrwr.pd = pd;
		umrwr.wr.send_flags |= MLX5_IB_SEND_UMR_UPDATE_PD;
	}

	if (flags & IB_MR_REREG_ACCESS) {
		umrwr.access_flags = access_flags;
		umrwr.wr.send_flags |= MLX5_IB_SEND_UMR_UPDATE_ACCESS;
	}

	/* post send request to UMR QP */
	down(&umrc->sem);
	err = ib_post_send(umrc->qp, &umrwr.wr, &bad);

	if (err) {
		mlx5_ib_warn(dev, "post send failed, err %d\n", err);
	} else {
		wait_for_completion(&umr_context.done);
		if (umr_context.status != IB_WC_SUCCESS) {
			mlx5_ib_warn(dev, "reg umr failed (%u)\n",
				     umr_context.status);
			err = -EFAULT;
		}
	}

	up(&umrc->sem);
	if (flags & IB_MR_REREG_TRANS) {
		dma_unmap_single(ddev, dma, size, DMA_TO_DEVICE);
		kfree(mr_pas);
	}
	return err;
}