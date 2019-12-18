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
struct TYPE_5__ {TYPE_3__* pgdir; } ;
struct mlx5_db {TYPE_2__ u; int /*<<< orphan*/  index; } ;
struct TYPE_4__ {int /*<<< orphan*/  pgdir_mutex; } ;
struct mlx5_core_dev {TYPE_1__ priv; } ;
struct TYPE_6__ {int /*<<< orphan*/  list; int /*<<< orphan*/  fw_page; int /*<<< orphan*/  bitmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLX5_DB_PER_PAGE ; 
 int /*<<< orphan*/  __set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ bitmap_full (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (TYPE_3__*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlx5_fwp_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

void mlx5_db_free(struct mlx5_core_dev *dev, struct mlx5_db *db)
{
	mutex_lock(&dev->priv.pgdir_mutex);

	__set_bit(db->index, db->u.pgdir->bitmap);

	if (bitmap_full(db->u.pgdir->bitmap, MLX5_DB_PER_PAGE)) {
		mlx5_fwp_free(db->u.pgdir->fw_page);
		list_del(&db->u.pgdir->list);
		kfree(db->u.pgdir);
	}

	mutex_unlock(&dev->priv.pgdir_mutex);
}