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
struct TYPE_8__ {int /*<<< orphan*/  key; } ;
struct TYPE_7__ {int /*<<< orphan*/  psv_idx; } ;
struct TYPE_6__ {int /*<<< orphan*/  psv_idx; } ;
struct TYPE_5__ {int /*<<< orphan*/  device; } ;
struct mlx5_ib_mr {int umred; TYPE_4__ mmkey; struct mlx5_ib_mr* sig; TYPE_3__ psv_wire; TYPE_2__ psv_memory; TYPE_1__ ibmr; } ;
struct mlx5_ib_dev {int /*<<< orphan*/  mdev; } ;

/* Variables and functions */
 int destroy_mkey (struct mlx5_ib_dev*,struct mlx5_ib_mr*) ; 
 int /*<<< orphan*/  free_cached_mr (struct mlx5_ib_dev*,struct mlx5_ib_mr*) ; 
 int /*<<< orphan*/  kfree (struct mlx5_ib_mr*) ; 
 scalar_t__ mlx5_core_destroy_psv (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5_free_priv_descs (struct mlx5_ib_mr*) ; 
 int /*<<< orphan*/  mlx5_ib_warn (struct mlx5_ib_dev*,char*,...) ; 
 struct mlx5_ib_dev* to_mdev (int /*<<< orphan*/ ) ; 
 int unreg_umr (struct mlx5_ib_dev*,struct mlx5_ib_mr*) ; 

__attribute__((used)) static int clean_mr(struct mlx5_ib_mr *mr)
{
	struct mlx5_ib_dev *dev = to_mdev(mr->ibmr.device);
	int umred = mr->umred;
	int err;

	if (mr->sig) {
		if (mlx5_core_destroy_psv(dev->mdev,
					  mr->sig->psv_memory.psv_idx))
			mlx5_ib_warn(dev, "failed to destroy mem psv %d\n",
				     mr->sig->psv_memory.psv_idx);
		if (mlx5_core_destroy_psv(dev->mdev,
					  mr->sig->psv_wire.psv_idx))
			mlx5_ib_warn(dev, "failed to destroy wire psv %d\n",
				     mr->sig->psv_wire.psv_idx);
		kfree(mr->sig);
		mr->sig = NULL;
	}

	mlx5_free_priv_descs(mr);

	if (!umred) {
		err = destroy_mkey(dev, mr);
		if (err) {
			mlx5_ib_warn(dev, "failed to destroy mkey 0x%x (%d)\n",
				     mr->mmkey.key, err);
			return err;
		}
	} else {
		err = unreg_umr(dev, mr);
		if (err) {
			mlx5_ib_warn(dev, "failed unregister\n");
			return err;
		}
		free_cached_mr(dev, mr);
	}

	if (!umred)
		kfree(mr);

	return 0;
}