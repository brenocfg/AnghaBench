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
typedef  int /*<<< orphan*/  u64 ;
struct mlx5_ib_dev {int dummy; } ;
typedef  void ib_umem ;
struct ib_pd {TYPE_1__* uobject; int /*<<< orphan*/  device; } ;
struct TYPE_2__ {int /*<<< orphan*/  context; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 void* ERR_PTR (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (void*) ; 
 int /*<<< orphan*/  PTR_ERR (void*) ; 
 void* ib_umem_get (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ib_umem_release (void*) ; 
 int /*<<< orphan*/  mlx5_ib_cont_pages (void*,int /*<<< orphan*/ ,int*,int*,int*,int*) ; 
 int /*<<< orphan*/  mlx5_ib_dbg (struct mlx5_ib_dev*,char*,int,int,int,int) ; 
 int /*<<< orphan*/  mlx5_ib_err (struct mlx5_ib_dev*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5_ib_warn (struct mlx5_ib_dev*,char*) ; 
 struct mlx5_ib_dev* to_mdev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct ib_umem *mr_umem_get(struct ib_pd *pd, u64 start, u64 length,
				   int access_flags, int *npages,
				   int *page_shift, int *ncont, int *order)
{
	struct mlx5_ib_dev *dev = to_mdev(pd->device);
	struct ib_umem *umem = ib_umem_get(pd->uobject->context, start, length,
					   access_flags, 0);
	if (IS_ERR(umem)) {
		mlx5_ib_err(dev, "umem get failed (%ld)\n", PTR_ERR(umem));
		return (void *)umem;
	}

	mlx5_ib_cont_pages(umem, start, npages, page_shift, ncont, order);
	if (!*npages) {
		mlx5_ib_warn(dev, "avoid zero region\n");
		ib_umem_release(umem);
		return ERR_PTR(-EINVAL);
	}

	mlx5_ib_dbg(dev, "npages %d, ncont %d, order %d, page_shift %d\n",
		    *npages, *ncont, *order, *page_shift);

	return umem;
}