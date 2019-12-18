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
struct mlx5_uuar_info {int num_uars; TYPE_1__* uars; TYPE_1__* bfs; TYPE_1__* bitmap; TYPE_1__* count; } ;
struct mlx5_core_dev {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  index; int /*<<< orphan*/  map; } ;

/* Variables and functions */
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (TYPE_1__*) ; 
 int /*<<< orphan*/  mlx5_cmd_free_uar (struct mlx5_core_dev*,int /*<<< orphan*/ ) ; 

int mlx5_free_uuars(struct mlx5_core_dev *dev, struct mlx5_uuar_info *uuari)
{
	int i = uuari->num_uars;

	for (i--; i >= 0; i--) {
		iounmap(uuari->uars[i].map);
		mlx5_cmd_free_uar(dev, uuari->uars[i].index);
	}

	kfree(uuari->count);
	kfree(uuari->bitmap);
	kfree(uuari->bfs);
	kfree(uuari->uars);

	return 0;
}