#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_6__ {int /*<<< orphan*/  key; } ;
struct ib_mr {int /*<<< orphan*/  lkey; int /*<<< orphan*/  rkey; } ;
struct mlx4_ib_mr {TYPE_2__ mmr; struct ib_mr ibmr; int /*<<< orphan*/ * umem; int /*<<< orphan*/  max_pages; } ;
struct mlx4_ib_dev {int /*<<< orphan*/  dev; } ;
struct ib_pd {int /*<<< orphan*/  device; } ;
typedef  enum ib_mr_type { ____Placeholder_ib_mr_type } ib_mr_type ;
struct TYPE_5__ {int /*<<< orphan*/  pdn; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 struct ib_mr* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int IB_MR_TYPE_MEM_REG ; 
 int /*<<< orphan*/  MLX4_MAX_FAST_REG_PAGES ; 
 int /*<<< orphan*/  kfree (struct mlx4_ib_mr*) ; 
 struct mlx4_ib_mr* kzalloc (int,int /*<<< orphan*/ ) ; 
 int mlx4_alloc_priv_pages (int /*<<< orphan*/ ,struct mlx4_ib_mr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx4_free_priv_pages (struct mlx4_ib_mr*) ; 
 int mlx4_mr_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int mlx4_mr_enable (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  mlx4_mr_free (int /*<<< orphan*/ ,TYPE_2__*) ; 
 struct mlx4_ib_dev* to_mdev (int /*<<< orphan*/ ) ; 
 TYPE_1__* to_mpd (struct ib_pd*) ; 

struct ib_mr *mlx4_ib_alloc_mr(struct ib_pd *pd,
			       enum ib_mr_type mr_type,
			       u32 max_num_sg)
{
	struct mlx4_ib_dev *dev = to_mdev(pd->device);
	struct mlx4_ib_mr *mr;
	int err;

	if (mr_type != IB_MR_TYPE_MEM_REG ||
	    max_num_sg > MLX4_MAX_FAST_REG_PAGES)
		return ERR_PTR(-EINVAL);

	mr = kzalloc(sizeof(*mr), GFP_KERNEL);
	if (!mr)
		return ERR_PTR(-ENOMEM);

	err = mlx4_mr_alloc(dev->dev, to_mpd(pd)->pdn, 0, 0, 0,
			    max_num_sg, 0, &mr->mmr);
	if (err)
		goto err_free;

	err = mlx4_alloc_priv_pages(pd->device, mr, max_num_sg);
	if (err)
		goto err_free_mr;

	mr->max_pages = max_num_sg;

	err = mlx4_mr_enable(dev->dev, &mr->mmr);
	if (err)
		goto err_free_pl;

	mr->ibmr.rkey = mr->ibmr.lkey = mr->mmr.key;
	mr->umem = NULL;

	return &mr->ibmr;

err_free_pl:
	mlx4_free_priv_pages(mr);
err_free_mr:
	(void) mlx4_mr_free(dev->dev, &mr->mmr);
err_free:
	kfree(mr);
	return ERR_PTR(err);
}