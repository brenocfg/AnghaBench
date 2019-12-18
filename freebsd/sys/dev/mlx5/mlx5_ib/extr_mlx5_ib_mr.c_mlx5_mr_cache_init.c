#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct mlx5_mr_cache {int /*<<< orphan*/  wq; struct mlx5_cache_ent* ent; } ;
struct mlx5_ib_dev {TYPE_3__* mdev; int /*<<< orphan*/  delay_timer; int /*<<< orphan*/  slow_path_mutex; struct mlx5_mr_cache cache; } ;
struct mlx5_cache_ent {int order; int limit; int /*<<< orphan*/  work; int /*<<< orphan*/  dwork; struct mlx5_ib_dev* dev; int /*<<< orphan*/  lock; int /*<<< orphan*/  head; } ;
struct TYPE_6__ {TYPE_2__* profile; } ;
struct TYPE_5__ {int mask; TYPE_1__* mr_cache; } ;
struct TYPE_4__ {int limit; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int MAX_MR_CACHE_ENTRIES ; 
 int MLX5_PROF_MASK_MR_CACHE ; 
 int /*<<< orphan*/  WQ_MEM_RECLAIM ; 
 int /*<<< orphan*/  alloc_ordered_workqueue (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cache_work_func ; 
 int /*<<< orphan*/  delay_time_func ; 
 int /*<<< orphan*/  delayed_cache_work_func ; 
 int /*<<< orphan*/  mlx5_ib_warn (struct mlx5_ib_dev*,char*) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  setup_timer (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

int mlx5_mr_cache_init(struct mlx5_ib_dev *dev)
{
	struct mlx5_mr_cache *cache = &dev->cache;
	struct mlx5_cache_ent *ent;
	int limit;
	int i;

	mutex_init(&dev->slow_path_mutex);
	cache->wq = alloc_ordered_workqueue("mkey_cache", WQ_MEM_RECLAIM);
	if (!cache->wq) {
		mlx5_ib_warn(dev, "failed to create work queue\n");
		return -ENOMEM;
	}

	setup_timer(&dev->delay_timer, delay_time_func, (unsigned long)dev);
	for (i = 0; i < MAX_MR_CACHE_ENTRIES; i++) {
		INIT_LIST_HEAD(&cache->ent[i].head);
		spin_lock_init(&cache->ent[i].lock);

		ent = &cache->ent[i];
		INIT_LIST_HEAD(&ent->head);
		spin_lock_init(&ent->lock);
		ent->order = i + 2;
		ent->dev = dev;

		if (dev->mdev->profile->mask & MLX5_PROF_MASK_MR_CACHE)
			limit = dev->mdev->profile->mr_cache[i].limit;
		else
			limit = 0;

		INIT_WORK(&ent->work, cache_work_func);
		INIT_DELAYED_WORK(&ent->dwork, delayed_cache_work_func);
		ent->limit = limit;
		queue_work(cache->wq, &ent->work);
	}

	return 0;
}