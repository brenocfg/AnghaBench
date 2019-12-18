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
typedef  size_t u8 ;
typedef  int u64 ;
struct mlx4_mac_table {int* refs; int* is_dup; scalar_t__ total; scalar_t__ max; int /*<<< orphan*/  mutex; void** entries; } ;
struct mlx4_port_info {struct mlx4_mac_table mac_table; } ;
struct mlx4_dev {int dummy; } ;
struct TYPE_2__ {struct mlx4_port_info* port; } ;

/* Variables and functions */
 int ENOSPC ; 
 int MLX4_MAC_MASK ; 
 int MLX4_MAC_VALID ; 
 int MLX4_MAX_MAC_NUM ; 
 int /*<<< orphan*/  SINGLE_DEPTH_NESTING ; 
 int be64_to_cpu (void*) ; 
 void* cpu_to_be64 (int) ; 
 int /*<<< orphan*/  mlx4_dbg (struct mlx4_dev*,char*,int,...) ; 
 int /*<<< orphan*/  mlx4_err (struct mlx4_dev*,char*,unsigned long long) ; 
 int mlx4_is_mf_bonded (struct mlx4_dev*) ; 
 int mlx4_need_mf_bond (struct mlx4_dev*) ; 
 TYPE_1__* mlx4_priv (struct mlx4_dev*) ; 
 int mlx4_set_port_mac_table (struct mlx4_dev*,size_t,void**) ; 
 int /*<<< orphan*/  mlx4_warn (struct mlx4_dev*,char*,...) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock_nested (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

int __mlx4_register_mac(struct mlx4_dev *dev, u8 port, u64 mac)
{
	struct mlx4_port_info *info = &mlx4_priv(dev)->port[port];
	struct mlx4_mac_table *table = &info->mac_table;
	int i, err = 0;
	int free = -1;
	int free_for_dup = -1;
	bool dup = mlx4_is_mf_bonded(dev);
	u8 dup_port = (port == 1) ? 2 : 1;
	struct mlx4_mac_table *dup_table = &mlx4_priv(dev)->port[dup_port].mac_table;
	bool need_mf_bond = mlx4_need_mf_bond(dev);
	bool can_mf_bond = true;

	mlx4_dbg(dev, "Registering MAC: 0x%llx for port %d %s duplicate\n",
		 (unsigned long long)mac, port,
		 dup ? "with" : "without");

	if (need_mf_bond) {
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

	if (need_mf_bond) {
		int index_at_port = -1;
		int index_at_dup_port = -1;

		for (i = 0; i < MLX4_MAX_MAC_NUM; i++) {
			if (((MLX4_MAC_MASK & mac) == (MLX4_MAC_MASK & be64_to_cpu(table->entries[i]))))
				index_at_port = i;
			if (((MLX4_MAC_MASK & mac) == (MLX4_MAC_MASK & be64_to_cpu(dup_table->entries[i]))))
				index_at_dup_port = i;
		}

		/* check that same mac is not in the tables at different indices */
		if ((index_at_port != index_at_dup_port) &&
		    (index_at_port >= 0) &&
		    (index_at_dup_port >= 0))
			can_mf_bond = false;

		/* If the mac is already in the primary table, the slot must be
		 * available in the duplicate table as well.
		 */
		if (index_at_port >= 0 && index_at_dup_port < 0 &&
		    dup_table->refs[index_at_port]) {
			can_mf_bond = false;
		}
		/* If the mac is already in the duplicate table, check that the
		 * corresponding index is not occupied in the primary table, or
		 * the primary table already contains the mac at the same index.
		 * Otherwise, you cannot bond (primary contains a different mac
		 * at that index).
		 */
		if (index_at_dup_port >= 0) {
			if (!table->refs[index_at_dup_port] ||
			    ((MLX4_MAC_MASK & mac) == (MLX4_MAC_MASK & be64_to_cpu(table->entries[index_at_dup_port]))))
				free_for_dup = index_at_dup_port;
			else
				can_mf_bond = false;
		}
	}

	for (i = 0; i < MLX4_MAX_MAC_NUM; i++) {
		if (!table->refs[i]) {
			if (free < 0)
				free = i;
			if (free_for_dup < 0 && need_mf_bond && can_mf_bond) {
				if (!dup_table->refs[i])
					free_for_dup = i;
			}
			continue;
		}

		if ((MLX4_MAC_MASK & mac) ==
		     (MLX4_MAC_MASK & be64_to_cpu(table->entries[i]))) {
			/* MAC already registered, increment ref count */
			err = i;
			++table->refs[i];
			if (dup) {
				u64 dup_mac = MLX4_MAC_MASK & be64_to_cpu(dup_table->entries[i]);

				if (dup_mac != mac || !dup_table->is_dup[i]) {
					mlx4_warn(dev, "register mac: expect duplicate mac 0x%llx on port %d index %d\n",
						  (long long)mac, dup_port, i);
				}
			}
			goto out;
		}
	}

	if (need_mf_bond && (free_for_dup < 0)) {
		if (dup) {
			mlx4_warn(dev, "Fail to allocate duplicate MAC table entry\n");
			mlx4_warn(dev, "High Availability for virtual functions may not work as expected\n");
			dup = false;
		}
		can_mf_bond = false;
	}

	if (need_mf_bond && can_mf_bond)
		free = free_for_dup;

	mlx4_dbg(dev, "Free MAC index is %d\n", free);

	if (table->total == table->max) {
		/* No free mac entries */
		err = -ENOSPC;
		goto out;
	}

	/* Register new MAC */
	table->entries[free] = cpu_to_be64(mac | MLX4_MAC_VALID);

	err = mlx4_set_port_mac_table(dev, port, table->entries);
	if (unlikely(err)) {
		mlx4_err(dev, "Failed adding MAC: 0x%llx\n",
			 (unsigned long long) mac);
		table->entries[free] = 0;
		goto out;
	}
	table->refs[free] = 1;
	table->is_dup[free] = false;
	++table->total;
	if (dup) {
		dup_table->refs[free] = 0;
		dup_table->is_dup[free] = true;
		dup_table->entries[free] = cpu_to_be64(mac | MLX4_MAC_VALID);

		err = mlx4_set_port_mac_table(dev, dup_port, dup_table->entries);
		if (unlikely(err)) {
			mlx4_warn(dev, "Failed adding duplicate mac: 0x%llx\n", (long long)mac);
			dup_table->is_dup[free] = false;
			dup_table->entries[free] = 0;
			goto out;
		}
		++dup_table->total;
	}
	err = free;
out:
	if (need_mf_bond) {
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
	return err;
}