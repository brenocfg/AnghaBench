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
struct mlx5_mr_cache {int /*<<< orphan*/  wq; struct mlx5_cache_ent* ent; } ;
struct mlx5_ib_mr {int /*<<< orphan*/  list; int /*<<< orphan*/  order; } ;
struct mlx5_ib_dev {struct mlx5_mr_cache cache; } ;
struct mlx5_cache_ent {int cur; int limit; int /*<<< orphan*/  work; int /*<<< orphan*/  lock; int /*<<< orphan*/  head; } ;

/* Variables and functions */
 int MAX_MR_CACHE_ENTRIES ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlx5_ib_warn (struct mlx5_ib_dev*,char*,int /*<<< orphan*/ ,int) ; 
 int order2idx (struct mlx5_ib_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void free_cached_mr(struct mlx5_ib_dev *dev, struct mlx5_ib_mr *mr)
{
	struct mlx5_mr_cache *cache = &dev->cache;
	struct mlx5_cache_ent *ent;
	int shrink = 0;
	int c;

	c = order2idx(dev, mr->order);
	if (c < 0 || c >= MAX_MR_CACHE_ENTRIES) {
		mlx5_ib_warn(dev, "order %d, cache index %d\n", mr->order, c);
		return;
	}
	ent = &cache->ent[c];
	spin_lock_irq(&ent->lock);
	list_add_tail(&mr->list, &ent->head);
	ent->cur++;
	if (ent->cur > 2 * ent->limit)
		shrink = 1;
	spin_unlock_irq(&ent->lock);

	if (shrink)
		queue_work(cache->wq, &ent->work);
}