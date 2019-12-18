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
struct mlx5_mr_cache {int /*<<< orphan*/  wq; scalar_t__ last_add; struct mlx5_cache_ent* ent; scalar_t__ stopped; } ;
struct mlx5_ib_dev {int /*<<< orphan*/  fill_delay; struct mlx5_mr_cache cache; } ;
struct mlx5_cache_ent {int cur; int limit; int /*<<< orphan*/  dwork; int /*<<< orphan*/  work; int /*<<< orphan*/  order; struct mlx5_ib_dev* dev; } ;

/* Variables and functions */
 int EAGAIN ; 
 int HZ ; 
 int add_keys (struct mlx5_ib_dev*,int,int) ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  mlx5_ib_dbg (struct mlx5_ib_dev*,char*,int) ; 
 int /*<<< orphan*/  mlx5_ib_warn (struct mlx5_ib_dev*,char*,int,int) ; 
 int msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  need_resched () ; 
 int order2idx (struct mlx5_ib_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  queue_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  remove_keys (struct mlx5_ib_dev*,int,int) ; 
 int /*<<< orphan*/  someone_adding (struct mlx5_mr_cache*) ; 
 scalar_t__ time_after (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void __cache_work_func(struct mlx5_cache_ent *ent)
{
	struct mlx5_ib_dev *dev = ent->dev;
	struct mlx5_mr_cache *cache = &dev->cache;
	int i = order2idx(dev, ent->order);
	int err;

	if (cache->stopped)
		return;

	ent = &dev->cache.ent[i];
	if (ent->cur < 2 * ent->limit && !dev->fill_delay) {
		err = add_keys(dev, i, 1);
		if (ent->cur < 2 * ent->limit) {
			if (err == -EAGAIN) {
				mlx5_ib_dbg(dev, "returned eagain, order %d\n",
					    i + 2);
				queue_delayed_work(cache->wq, &ent->dwork,
						   msecs_to_jiffies(3));
			} else if (err) {
				mlx5_ib_warn(dev, "command failed order %d, err %d\n",
					     i + 2, err);
				queue_delayed_work(cache->wq, &ent->dwork,
						   msecs_to_jiffies(1000));
			} else {
				queue_work(cache->wq, &ent->work);
			}
		}
	} else if (ent->cur > 2 * ent->limit) {
		/*
		 * The remove_keys() logic is performed as garbage collection
		 * task. Such task is intended to be run when no other active
		 * processes are running.
		 *
		 * The need_resched() will return TRUE if there are user tasks
		 * to be activated in near future.
		 *
		 * In such case, we don't execute remove_keys() and postpone
		 * the garbage collection work to try to run in next cycle,
		 * in order to free CPU resources to other tasks.
		 */
		if (!need_resched() && !someone_adding(cache) &&
		    time_after(jiffies, cache->last_add + 300 * HZ)) {
			remove_keys(dev, i, 1);
			if (ent->cur > ent->limit)
				queue_work(cache->wq, &ent->work);
		} else {
			queue_delayed_work(cache->wq, &ent->dwork, 300 * HZ);
		}
	}
}