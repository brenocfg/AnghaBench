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
struct mlx5_flow_table {int dummy; } ;
struct list_head {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  lock; } ;
struct fs_prio {TYPE_1__ base; } ;

/* Variables and functions */
 struct mlx5_flow_table* _find_first_ft_in_prio (struct fs_prio*,struct list_head*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct mlx5_flow_table *find_first_ft_in_prio(struct fs_prio *prio,
						     struct list_head *start)
{
	struct mlx5_flow_table *ft;

	if (!prio)
		return NULL;

	mutex_lock(&prio->base.lock);
	ft = _find_first_ft_in_prio(prio, start);
	mutex_unlock(&prio->base.lock);

	return ft;
}