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
struct mlx5_uuar_info {int num_uars; struct mlx5_bf* uars; struct mlx5_bf* bfs; struct mlx5_bf* bitmap; struct mlx5_bf* count; int /*<<< orphan*/  lock; int /*<<< orphan*/  num_low_latency_uuars; } ;
struct mlx5_core_dev {int /*<<< orphan*/  pdev; } ;
struct mlx5_bf {int buf_size; int uuarn; scalar_t__ index; int /*<<< orphan*/  map; int /*<<< orphan*/  lock32; int /*<<< orphan*/  lock; int /*<<< orphan*/  need_lock; scalar_t__ offset; int /*<<< orphan*/ * reg; int /*<<< orphan*/  regreg; struct mlx5_bf* uar; } ;
typedef  int phys_addr_t ;

/* Variables and functions */
 int BITS_TO_LONGS (int) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ MLX5_BF_OFFSET ; 
 int MLX5_BF_REGS_PER_PAGE ; 
 int MLX5_CAP_GEN (struct mlx5_core_dev*,int /*<<< orphan*/ ) ; 
 int NUM_DRIVER_UARS ; 
 int /*<<< orphan*/  NUM_LOW_LAT_UUARS ; 
 int PAGE_SHIFT ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  ioremap (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 void* kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct mlx5_bf*) ; 
 int /*<<< orphan*/  log_bf_reg_size ; 
 int mlx5_cmd_alloc_uar (struct mlx5_core_dev*,scalar_t__*) ; 
 int /*<<< orphan*/  mlx5_cmd_free_uar (struct mlx5_core_dev*,scalar_t__) ; 
 int /*<<< orphan*/  mlx5_core_dbg (struct mlx5_core_dev*,char*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  need_uuar_lock (int) ; 
 int pci_resource_start (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

int mlx5_alloc_uuars(struct mlx5_core_dev *dev, struct mlx5_uuar_info *uuari)
{
	int tot_uuars = NUM_DRIVER_UARS * MLX5_BF_REGS_PER_PAGE;
	struct mlx5_bf *bf;
	phys_addr_t addr;
	int err;
	int i;

	uuari->num_uars = NUM_DRIVER_UARS;
	uuari->num_low_latency_uuars = NUM_LOW_LAT_UUARS;

	mutex_init(&uuari->lock);
	uuari->uars = kcalloc(uuari->num_uars, sizeof(*uuari->uars), GFP_KERNEL);

	uuari->bfs = kcalloc(tot_uuars, sizeof(*uuari->bfs), GFP_KERNEL);

	uuari->bitmap = kcalloc(BITS_TO_LONGS(tot_uuars), sizeof(*uuari->bitmap),
				GFP_KERNEL);

	uuari->count = kcalloc(tot_uuars, sizeof(*uuari->count), GFP_KERNEL);

	for (i = 0; i < uuari->num_uars; i++) {
		err = mlx5_cmd_alloc_uar(dev, &uuari->uars[i].index);
		if (err)
			goto out_count;

		addr = pci_resource_start(dev->pdev, 0) +
		       ((phys_addr_t)(uuari->uars[i].index) << PAGE_SHIFT);
		uuari->uars[i].map = ioremap(addr, PAGE_SIZE);
		if (!uuari->uars[i].map) {
			mlx5_cmd_free_uar(dev, uuari->uars[i].index);
			err = -ENOMEM;
			goto out_count;
		}
		mlx5_core_dbg(dev, "allocated uar index 0x%x, mmaped at %p\n",
			      uuari->uars[i].index, uuari->uars[i].map);
	}

	for (i = 0; i < tot_uuars; i++) {
		bf = &uuari->bfs[i];

		bf->buf_size = (1 << MLX5_CAP_GEN(dev, log_bf_reg_size)) / 2;
		bf->uar = &uuari->uars[i / MLX5_BF_REGS_PER_PAGE];
		bf->regreg = uuari->uars[i / MLX5_BF_REGS_PER_PAGE].map;
		bf->reg = NULL; /* Add WC support */
		bf->offset = (i % MLX5_BF_REGS_PER_PAGE) *
			     (1 << MLX5_CAP_GEN(dev, log_bf_reg_size)) +
			     MLX5_BF_OFFSET;
		bf->need_lock = need_uuar_lock(i);
		spin_lock_init(&bf->lock);
		spin_lock_init(&bf->lock32);
		bf->uuarn = i;
	}

	return 0;

out_count:
	for (i--; i >= 0; i--) {
		iounmap(uuari->uars[i].map);
		mlx5_cmd_free_uar(dev, uuari->uars[i].index);
	}
	kfree(uuari->count);

	kfree(uuari->bitmap);

	kfree(uuari->bfs);

	kfree(uuari->uars);
	return err;
}