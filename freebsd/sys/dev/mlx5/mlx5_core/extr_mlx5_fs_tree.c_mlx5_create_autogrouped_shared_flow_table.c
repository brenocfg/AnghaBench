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
struct mlx5_flow_table {int /*<<< orphan*/  shared_refcount; } ;
struct fs_prio {int /*<<< orphan*/  objs; } ;

/* Variables and functions */
 struct mlx5_flow_table* find_first_ft_in_prio (struct fs_prio*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct mlx5_flow_table *mlx5_create_autogrouped_shared_flow_table(struct fs_prio *fs_prio)
{
	struct mlx5_flow_table *ft;

	ft = find_first_ft_in_prio(fs_prio, &fs_prio->objs);
	if (ft) {
		ft->shared_refcount++;
		return ft;
	}

	return NULL;
}