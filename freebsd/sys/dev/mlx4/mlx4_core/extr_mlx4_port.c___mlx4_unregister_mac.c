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
typedef  int u8 ;
typedef  int /*<<< orphan*/  u64 ;
struct mlx4_mac_table {int* is_dup; int /*<<< orphan*/  mutex; int /*<<< orphan*/  total; scalar_t__* entries; scalar_t__* refs; } ;
struct mlx4_port_info {struct mlx4_mac_table mac_table; } ;
struct TYPE_3__ {int num_ports; } ;
struct mlx4_dev {TYPE_1__ caps; } ;
struct TYPE_4__ {struct mlx4_port_info* port; } ;

/* Variables and functions */
 int /*<<< orphan*/  SINGLE_DEPTH_NESTING ; 
 int find_index (struct mlx4_dev*,struct mlx4_mac_table*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx4_dbg (struct mlx4_dev*,char*,int) ; 
 int mlx4_is_mf_bonded (struct mlx4_dev*) ; 
 TYPE_2__* mlx4_priv (struct mlx4_dev*) ; 
 scalar_t__ mlx4_set_port_mac_table (struct mlx4_dev*,int,scalar_t__*) ; 
 int /*<<< orphan*/  mlx4_warn (struct mlx4_dev*,char*,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock_nested (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ validate_index (struct mlx4_dev*,struct mlx4_mac_table*,int) ; 

void __mlx4_unregister_mac(struct mlx4_dev *dev, u8 port, u64 mac)
{
	struct mlx4_port_info *info;
	struct mlx4_mac_table *table;
	int index;
	bool dup = mlx4_is_mf_bonded(dev);
	u8 dup_port = (port == 1) ? 2 : 1;
	struct mlx4_mac_table *dup_table = &mlx4_priv(dev)->port[dup_port].mac_table;

	if (port < 1 || port > dev->caps.num_ports) {
		mlx4_warn(dev, "invalid port number (%d), aborting...\n", port);
		return;
	}
	info = &mlx4_priv(dev)->port[port];
	table = &info->mac_table;

	if (dup) {
		if (port == 1) {
			mutex_lock(&table->mutex);
			mutex_lock_nested(&dup_table->mutex, SINGLE_DEPTH_NESTING);
		} else {
			mutex_lock(&dup_table->mutex);
			mutex_lock_nested(&table->mutex, SINGLE_DEPTH_NESTING);
		}
	} else {
		mutex_lock(&table->mutex);
	}

	index = find_index(dev, table, mac);

	if (validate_index(dev, table, index))
		goto out;

	if (--table->refs[index] || table->is_dup[index]) {
		mlx4_dbg(dev, "Have more references for index %d, no need to modify mac table\n",
			 index);
		if (!table->refs[index])
			dup_table->is_dup[index] = false;
		goto out;
	}

	table->entries[index] = 0;
	if (mlx4_set_port_mac_table(dev, port, table->entries))
		mlx4_warn(dev, "Fail to set mac in port %d during unregister\n", port);
	--table->total;

	if (dup) {
		dup_table->is_dup[index] = false;
		if (dup_table->refs[index])
			goto out;
		dup_table->entries[index] = 0;
		if (mlx4_set_port_mac_table(dev, dup_port, dup_table->entries))
			mlx4_warn(dev, "Fail to set mac in duplicate port %d during unregister\n", dup_port);

		--table->total;
	}
out:
	if (dup) {
		if (port == 2) {
			mutex_unlock(&table->mutex);
			mutex_unlock(&dup_table->mutex);
		} else {
			mutex_unlock(&dup_table->mutex);
			mutex_unlock(&table->mutex);
		}
	} else {
		mutex_unlock(&table->mutex);
	}
}