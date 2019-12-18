#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
struct TYPE_14__ {int /*<<< orphan*/  key; int /*<<< orphan*/  mtt; } ;
struct ib_mr {int /*<<< orphan*/  lkey; int /*<<< orphan*/  rkey; } ;
struct mlx4_ib_mr {TYPE_6__* umem; TYPE_3__ mmr; struct ib_mr ibmr; } ;
struct mlx4_ib_dev {int /*<<< orphan*/  dev; } ;
struct ib_udata {int dummy; } ;
struct ib_pd {int /*<<< orphan*/  device; TYPE_1__* uobject; } ;
struct TYPE_15__ {int /*<<< orphan*/  page_size; } ;
struct TYPE_13__ {int /*<<< orphan*/  pdn; } ;
struct TYPE_12__ {int /*<<< orphan*/  context; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct ib_mr* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int IB_ACCESS_LOCAL_WRITE ; 
 scalar_t__ IS_ERR (TYPE_6__*) ; 
 int PTR_ERR (TYPE_6__*) ; 
 int /*<<< orphan*/  convert_access (int) ; 
 TYPE_6__* ib_umem_get (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int ib_umem_page_count (TYPE_6__*) ; 
 int /*<<< orphan*/  ib_umem_release (TYPE_6__*) ; 
 int ilog2 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct mlx4_ib_mr*) ; 
 struct mlx4_ib_mr* kzalloc (int,int /*<<< orphan*/ ) ; 
 int mlx4_ib_umem_write_mtt (struct mlx4_ib_dev*,int /*<<< orphan*/ *,TYPE_6__*) ; 
 int mlx4_mr_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,TYPE_3__*) ; 
 int mlx4_mr_enable (int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  mlx4_mr_free (int /*<<< orphan*/ ,TYPE_3__*) ; 
 struct mlx4_ib_dev* to_mdev (int /*<<< orphan*/ ) ; 
 TYPE_2__* to_mpd (struct ib_pd*) ; 

struct ib_mr *mlx4_ib_reg_user_mr(struct ib_pd *pd, u64 start, u64 length,
				  u64 virt_addr, int access_flags,
				  struct ib_udata *udata)
{
	struct mlx4_ib_dev *dev = to_mdev(pd->device);
	struct mlx4_ib_mr *mr;
	int shift;
	int err;
	int n;

	mr = kzalloc(sizeof(*mr), GFP_KERNEL);
	if (!mr)
		return ERR_PTR(-ENOMEM);

	/* Force registering the memory as writable. */
	/* Used for memory re-registeration. HCA protects the access */
	mr->umem = ib_umem_get(pd->uobject->context, start, length,
			       access_flags | IB_ACCESS_LOCAL_WRITE, 0);
	if (IS_ERR(mr->umem)) {
		err = PTR_ERR(mr->umem);
		goto err_free;
	}

	n = ib_umem_page_count(mr->umem);
	shift = ilog2(mr->umem->page_size);

	err = mlx4_mr_alloc(dev->dev, to_mpd(pd)->pdn, virt_addr, length,
			    convert_access(access_flags), n, shift, &mr->mmr);
	if (err)
		goto err_umem;

	err = mlx4_ib_umem_write_mtt(dev, &mr->mmr.mtt, mr->umem);
	if (err)
		goto err_mr;

	err = mlx4_mr_enable(dev->dev, &mr->mmr);
	if (err)
		goto err_mr;

	mr->ibmr.rkey = mr->ibmr.lkey = mr->mmr.key;

	return &mr->ibmr;

err_mr:
	(void) mlx4_mr_free(to_mdev(pd->device)->dev, &mr->mmr);

err_umem:
	ib_umem_release(mr->umem);

err_free:
	kfree(mr);

	return ERR_PTR(err);
}