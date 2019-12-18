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
struct mlx5_ib_mr {int order; int umred; int /*<<< orphan*/  out; int /*<<< orphan*/  mmkey; struct mlx5_ib_dev* dev; } ;
typedef  struct mlx5_ib_mr u32 ;
struct mlx5_mr_cache {struct mlx5_cache_ent* ent; } ;
struct mlx5_ib_dev {int /*<<< orphan*/  mdev; struct mlx5_mr_cache cache; } ;
struct mlx5_cache_ent {int order; scalar_t__ pending; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int EAGAIN ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ MAX_PENDING_REG_MR ; 
 int MLX5_ACCESS_MODE_MTT ; 
 void* MLX5_ADDR_OF (int /*<<< orphan*/ ,struct mlx5_ib_mr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MLX5_SET (void*,void*,int /*<<< orphan*/ ,int) ; 
 int MLX5_ST_SZ_BYTES (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  access_mode ; 
 int /*<<< orphan*/  create_mkey_in ; 
 int /*<<< orphan*/  free ; 
 int /*<<< orphan*/  kfree (struct mlx5_ib_mr*) ; 
 struct mlx5_ib_mr* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_page_size ; 
 int /*<<< orphan*/  memory_key_mkey_entry ; 
 int mlx5_core_create_mkey_cb (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct mlx5_ib_mr*,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct mlx5_ib_mr*) ; 
 int /*<<< orphan*/  mlx5_ib_warn (struct mlx5_ib_dev*,char*,int) ; 
 int /*<<< orphan*/  qpn ; 
 int /*<<< orphan*/  reg_mr_callback ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  translations_octword_size ; 
 int /*<<< orphan*/  umr_en ; 

__attribute__((used)) static int add_keys(struct mlx5_ib_dev *dev, int c, int num)
{
	struct mlx5_mr_cache *cache = &dev->cache;
	struct mlx5_cache_ent *ent = &cache->ent[c];
	int inlen = MLX5_ST_SZ_BYTES(create_mkey_in);
	struct mlx5_ib_mr *mr;
	int npages = 1 << ent->order;
	void *mkc;
	u32 *in;
	int err = 0;
	int i;

	in = kzalloc(inlen, GFP_KERNEL);
	if (!in)
		return -ENOMEM;

	mkc = MLX5_ADDR_OF(create_mkey_in, in, memory_key_mkey_entry);
	for (i = 0; i < num; i++) {
		if (ent->pending >= MAX_PENDING_REG_MR) {
			err = -EAGAIN;
			break;
		}

		mr = kzalloc(sizeof(*mr), GFP_KERNEL);
		if (!mr) {
			err = -ENOMEM;
			break;
		}
		mr->order = ent->order;
		mr->umred = 1;
		mr->dev = dev;

		MLX5_SET(mkc, mkc, free, 1);
		MLX5_SET(mkc, mkc, umr_en, 1);
		MLX5_SET(mkc, mkc, access_mode, MLX5_ACCESS_MODE_MTT);

		MLX5_SET(mkc, mkc, qpn, 0xffffff);
		MLX5_SET(mkc, mkc, translations_octword_size, (npages + 1) / 2);
		MLX5_SET(mkc, mkc, log_page_size, 12);

		spin_lock_irq(&ent->lock);
		ent->pending++;
		spin_unlock_irq(&ent->lock);
		err = mlx5_core_create_mkey_cb(dev->mdev, &mr->mmkey,
					       in, inlen,
					       mr->out, sizeof(mr->out),
					       reg_mr_callback, mr);
		if (err) {
			spin_lock_irq(&ent->lock);
			ent->pending--;
			spin_unlock_irq(&ent->lock);
			mlx5_ib_warn(dev, "create mkey failed %d\n", err);
			kfree(mr);
			break;
		}
	}

	kfree(in);
	return err;
}