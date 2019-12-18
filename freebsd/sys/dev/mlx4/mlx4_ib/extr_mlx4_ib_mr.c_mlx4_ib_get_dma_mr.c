#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  key; } ;
struct ib_mr {int /*<<< orphan*/  lkey; int /*<<< orphan*/  rkey; } ;
struct mlx4_ib_mr {TYPE_3__ mmr; struct ib_mr ibmr; int /*<<< orphan*/ * umem; } ;
struct ib_pd {int /*<<< orphan*/  device; } ;
struct TYPE_7__ {int /*<<< orphan*/  dev; } ;
struct TYPE_6__ {int /*<<< orphan*/  pdn; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct ib_mr* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  convert_access (int) ; 
 int /*<<< orphan*/  kfree (struct mlx4_ib_mr*) ; 
 struct mlx4_ib_mr* kzalloc (int,int /*<<< orphan*/ ) ; 
 int mlx4_mr_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long long,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*) ; 
 int mlx4_mr_enable (int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  mlx4_mr_free (int /*<<< orphan*/ ,TYPE_3__*) ; 
 TYPE_2__* to_mdev (int /*<<< orphan*/ ) ; 
 TYPE_1__* to_mpd (struct ib_pd*) ; 

struct ib_mr *mlx4_ib_get_dma_mr(struct ib_pd *pd, int acc)
{
	struct mlx4_ib_mr *mr;
	int err;

	mr = kzalloc(sizeof(*mr), GFP_KERNEL);
	if (!mr)
		return ERR_PTR(-ENOMEM);

	err = mlx4_mr_alloc(to_mdev(pd->device)->dev, to_mpd(pd)->pdn, 0,
			    ~0ull, convert_access(acc), 0, 0, &mr->mmr);
	if (err)
		goto err_free;

	err = mlx4_mr_enable(to_mdev(pd->device)->dev, &mr->mmr);
	if (err)
		goto err_mr;

	mr->ibmr.rkey = mr->ibmr.lkey = mr->mmr.key;
	mr->umem = NULL;

	return &mr->ibmr;

err_mr:
	(void) mlx4_mr_free(to_mdev(pd->device)->dev, &mr->mmr);

err_free:
	kfree(mr);

	return ERR_PTR(err);
}