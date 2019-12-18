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
struct mlx5_core_dev {int dummy; } ;
struct mlx5_cmd_msg {TYPE_1__* cache; int /*<<< orphan*/  list; } ;
struct TYPE_2__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  head; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlx5_free_cmd_msg (struct mlx5_core_dev*,struct mlx5_cmd_msg*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void free_msg(struct mlx5_core_dev *dev, struct mlx5_cmd_msg *msg)
{
	unsigned long flags;

	if (msg->cache) {
		spin_lock_irqsave(&msg->cache->lock, flags);
		list_add_tail(&msg->list, &msg->cache->head);
		spin_unlock_irqrestore(&msg->cache->lock, flags);
	} else {
		mlx5_free_cmd_msg(dev, msg);
	}
}