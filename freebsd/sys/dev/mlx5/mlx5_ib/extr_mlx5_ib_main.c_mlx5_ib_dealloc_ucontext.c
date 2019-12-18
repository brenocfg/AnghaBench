#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct mlx5_uuar_info {int num_uars; struct mlx5_ib_ucontext* uars; struct mlx5_ib_ucontext* bitmap; struct mlx5_ib_ucontext* count; } ;
struct mlx5_ib_ucontext {int /*<<< orphan*/  index; int /*<<< orphan*/  tdn; struct mlx5_uuar_info uuari; } ;
struct mlx5_ib_dev {int /*<<< orphan*/  mdev; } ;
struct ib_ucontext {int /*<<< orphan*/  device; } ;

/* Variables and functions */
 scalar_t__ MLX5_CAP_GEN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct mlx5_ib_ucontext*) ; 
 int /*<<< orphan*/  log_max_transport_domain ; 
 scalar_t__ mlx5_cmd_free_uar (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5_dealloc_transport_domain (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5_ib_warn (struct mlx5_ib_dev*,char*,int /*<<< orphan*/ ) ; 
 struct mlx5_ib_dev* to_mdev (int /*<<< orphan*/ ) ; 
 struct mlx5_ib_ucontext* to_mucontext (struct ib_ucontext*) ; 

__attribute__((used)) static int mlx5_ib_dealloc_ucontext(struct ib_ucontext *ibcontext)
{
	struct mlx5_ib_ucontext *context = to_mucontext(ibcontext);
	struct mlx5_ib_dev *dev = to_mdev(ibcontext->device);
	struct mlx5_uuar_info *uuari = &context->uuari;
	int i;

	if (MLX5_CAP_GEN(dev->mdev, log_max_transport_domain))
		mlx5_dealloc_transport_domain(dev->mdev, context->tdn);

	for (i = 0; i < uuari->num_uars; i++) {
		if (mlx5_cmd_free_uar(dev->mdev, uuari->uars[i].index))
			mlx5_ib_warn(dev, "failed to free UAR 0x%x\n", uuari->uars[i].index);
	}

	kfree(uuari->count);
	kfree(uuari->bitmap);
	kfree(uuari->uars);
	kfree(context);

	return 0;
}