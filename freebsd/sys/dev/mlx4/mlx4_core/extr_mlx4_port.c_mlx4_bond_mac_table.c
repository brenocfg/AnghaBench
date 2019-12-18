#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct mlx4_mac_table {scalar_t__* entries; int* is_dup; int /*<<< orphan*/  mutex; } ;
struct mlx4_dev {int dummy; } ;
struct TYPE_4__ {TYPE_1__* port; } ;
struct TYPE_3__ {struct mlx4_mac_table mac_table; } ;

/* Variables and functions */
 int EINVAL ; 
 int MLX4_MAX_MAC_NUM ; 
 TYPE_2__* mlx4_priv (struct mlx4_dev*) ; 
 int mlx4_set_port_mac_table (struct mlx4_dev*,int,scalar_t__*) ; 
 int /*<<< orphan*/  mlx4_warn (struct mlx4_dev*,char*,...) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int mlx4_bond_mac_table(struct mlx4_dev *dev)
{
	struct mlx4_mac_table *t1 = &mlx4_priv(dev)->port[1].mac_table;
	struct mlx4_mac_table *t2 = &mlx4_priv(dev)->port[2].mac_table;
	int ret = 0;
	int i;
	bool update1 = false;
	bool update2 = false;

	mutex_lock(&t1->mutex);
	mutex_lock(&t2->mutex);
	for (i = 0; i < MLX4_MAX_MAC_NUM; i++) {
		if ((t1->entries[i] != t2->entries[i]) &&
		    t1->entries[i] && t2->entries[i]) {
			mlx4_warn(dev, "can't duplicate entry %d in mac table\n", i);
			ret = -EINVAL;
			goto unlock;
		}
	}

	for (i = 0; i < MLX4_MAX_MAC_NUM; i++) {
		if (t1->entries[i] && !t2->entries[i]) {
			t2->entries[i] = t1->entries[i];
			t2->is_dup[i] = true;
			update2 = true;
		} else if (!t1->entries[i] && t2->entries[i]) {
			t1->entries[i] = t2->entries[i];
			t1->is_dup[i] = true;
			update1 = true;
		} else if (t1->entries[i] && t2->entries[i]) {
			t1->is_dup[i] = true;
			t2->is_dup[i] = true;
		}
	}

	if (update1) {
		ret = mlx4_set_port_mac_table(dev, 1, t1->entries);
		if (ret)
			mlx4_warn(dev, "failed to set MAC table for port 1 (%d)\n", ret);
	}
	if (!ret && update2) {
		ret = mlx4_set_port_mac_table(dev, 2, t2->entries);
		if (ret)
			mlx4_warn(dev, "failed to set MAC table for port 2 (%d)\n", ret);
	}

	if (ret)
		mlx4_warn(dev, "failed to create mirror MAC tables\n");
unlock:
	mutex_unlock(&t2->mutex);
	mutex_unlock(&t1->mutex);
	return ret;
}