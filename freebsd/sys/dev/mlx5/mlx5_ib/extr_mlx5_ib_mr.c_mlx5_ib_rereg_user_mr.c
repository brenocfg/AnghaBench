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
typedef  void* u64 ;
struct TYPE_7__ {void* size; void* iova; int /*<<< orphan*/  pd; } ;
struct mlx5_ib_mr {int access_flags; void* address; void* length; TYPE_3__ mmkey; int /*<<< orphan*/  npages; scalar_t__ umred; struct mlx5_ib_mr* umem; } ;
struct mlx5_ib_dev {TYPE_2__* mdev; } ;
struct ib_udata {int dummy; } ;
struct ib_pd {int dummy; } ;
struct ib_mr {struct ib_pd* pd; int /*<<< orphan*/  device; } ;
struct TYPE_8__ {int /*<<< orphan*/  pdn; } ;
struct TYPE_5__ {int /*<<< orphan*/  reg_pages; } ;
struct TYPE_6__ {TYPE_1__ priv; } ;

/* Variables and functions */
 int IB_MR_REREG_ACCESS ; 
 int IB_MR_REREG_PD ; 
 int IB_MR_REREG_TRANS ; 
 scalar_t__ IS_ERR (struct mlx5_ib_mr*) ; 
 int PTR_ERR (struct mlx5_ib_mr*) ; 
 int /*<<< orphan*/  atomic_sub (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int destroy_mkey (struct mlx5_ib_dev*,struct mlx5_ib_mr*) ; 
 int /*<<< orphan*/  ib_umem_release (struct mlx5_ib_mr*) ; 
 int /*<<< orphan*/  mlx5_ib_dbg (struct mlx5_ib_dev*,char*,long long,long long,long long,int) ; 
 int /*<<< orphan*/  mlx5_ib_warn (struct mlx5_ib_dev*,char*) ; 
 struct mlx5_ib_mr* mr_umem_get (struct ib_pd*,void*,void*,int,int*,int*,int*,int*) ; 
 struct mlx5_ib_mr* reg_create (struct ib_mr*,struct ib_pd*,void*,void*,struct mlx5_ib_mr*,int,int,int) ; 
 int rereg_umr (struct ib_pd*,struct mlx5_ib_mr*,void*,void*,int,int,int,int,int) ; 
 int /*<<< orphan*/  set_mr_fileds (struct mlx5_ib_dev*,struct mlx5_ib_mr*,int,void*,int) ; 
 struct mlx5_ib_dev* to_mdev (int /*<<< orphan*/ ) ; 
 struct mlx5_ib_mr* to_mmr (struct ib_mr*) ; 
 TYPE_4__* to_mpd (struct ib_pd*) ; 
 int unreg_umr (struct mlx5_ib_dev*,struct mlx5_ib_mr*) ; 
 int /*<<< orphan*/  update_odp_mr (struct mlx5_ib_mr*) ; 
 int /*<<< orphan*/  use_umr_mtt_update (struct mlx5_ib_mr*,void*,void*) ; 

int mlx5_ib_rereg_user_mr(struct ib_mr *ib_mr, int flags, u64 start,
			  u64 length, u64 virt_addr, int new_access_flags,
			  struct ib_pd *new_pd, struct ib_udata *udata)
{
	struct mlx5_ib_dev *dev = to_mdev(ib_mr->device);
	struct mlx5_ib_mr *mr = to_mmr(ib_mr);
	struct ib_pd *pd = (flags & IB_MR_REREG_PD) ? new_pd : ib_mr->pd;
	int access_flags = flags & IB_MR_REREG_ACCESS ?
			    new_access_flags :
			    mr->access_flags;
	u64 addr = (flags & IB_MR_REREG_TRANS) ? virt_addr : mr->umem->address;
	u64 len = (flags & IB_MR_REREG_TRANS) ? length : mr->umem->length;
	int page_shift = 0;
	int npages = 0;
	int ncont = 0;
	int order = 0;
	int err;

	mlx5_ib_dbg(dev, "start 0x%llx, virt_addr 0x%llx, length 0x%llx, access_flags 0x%x\n",
		    (long long)start, (long long)virt_addr, (long long)length, access_flags);

	if (flags != IB_MR_REREG_PD) {
		/*
		 * Replace umem. This needs to be done whether or not UMR is
		 * used.
		 */
		flags |= IB_MR_REREG_TRANS;
		ib_umem_release(mr->umem);
		mr->umem = mr_umem_get(pd, addr, len, access_flags, &npages,
				       &page_shift, &ncont, &order);
		if (IS_ERR(mr->umem)) {
			err = PTR_ERR(mr->umem);
			mr->umem = NULL;
			return err;
		}
	}

	if (flags & IB_MR_REREG_TRANS && !use_umr_mtt_update(mr, addr, len)) {
		/*
		 * UMR can't be used - MKey needs to be replaced.
		 */
		if (mr->umred) {
			err = unreg_umr(dev, mr);
			if (err)
				mlx5_ib_warn(dev, "Failed to unregister MR\n");
		} else {
			err = destroy_mkey(dev, mr);
			if (err)
				mlx5_ib_warn(dev, "Failed to destroy MKey\n");
		}
		if (err)
			return err;

		mr = reg_create(ib_mr, pd, addr, len, mr->umem, ncont,
				page_shift, access_flags);

		if (IS_ERR(mr))
			return PTR_ERR(mr);

		mr->umred = 0;
	} else {
		/*
		 * Send a UMR WQE
		 */
		err = rereg_umr(pd, mr, addr, len, npages, page_shift,
				order, access_flags, flags);
		if (err) {
			mlx5_ib_warn(dev, "Failed to rereg UMR\n");
			return err;
		}
	}

	if (flags & IB_MR_REREG_PD) {
		ib_mr->pd = pd;
		mr->mmkey.pd = to_mpd(pd)->pdn;
	}

	if (flags & IB_MR_REREG_ACCESS)
		mr->access_flags = access_flags;

	if (flags & IB_MR_REREG_TRANS) {
		atomic_sub(mr->npages, &dev->mdev->priv.reg_pages);
		set_mr_fileds(dev, mr, npages, len, access_flags);
		mr->mmkey.iova = addr;
		mr->mmkey.size = len;
	}
#ifdef CONFIG_INFINIBAND_ON_DEMAND_PAGING
	update_odp_mr(mr);
#endif

	return 0;
}