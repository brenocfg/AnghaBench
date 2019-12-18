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
typedef  size_t u8 ;
struct ib_gid_table {int dummy; } ;
struct TYPE_4__ {struct ib_gid_table** gid_cache; } ;
struct ib_device {size_t phys_port_cnt; TYPE_2__ cache; TYPE_1__* port_immutable; int /*<<< orphan*/  name; } ;
struct TYPE_3__ {int /*<<< orphan*/  gid_tbl_len; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct ib_gid_table* alloc_gid_table (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cleanup_gid_table_port (struct ib_device*,size_t,struct ib_gid_table*) ; 
 int gid_table_reserve_default (struct ib_device*,size_t,struct ib_gid_table*) ; 
 struct ib_gid_table** kcalloc (size_t,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct ib_gid_table**) ; 
 int /*<<< orphan*/  pr_warn (char*,int /*<<< orphan*/ ) ; 
 size_t rdma_start_port (struct ib_device*) ; 
 int /*<<< orphan*/  release_gid_table (struct ib_gid_table*) ; 

__attribute__((used)) static int _gid_table_setup_one(struct ib_device *ib_dev)
{
	u8 port;
	struct ib_gid_table **table;
	int err = 0;

	table = kcalloc(ib_dev->phys_port_cnt, sizeof(*table), GFP_KERNEL);

	if (!table) {
		pr_warn("failed to allocate ib gid cache for %s\n",
			ib_dev->name);
		return -ENOMEM;
	}

	for (port = 0; port < ib_dev->phys_port_cnt; port++) {
		u8 rdma_port = port + rdma_start_port(ib_dev);

		table[port] =
			alloc_gid_table(
				ib_dev->port_immutable[rdma_port].gid_tbl_len);
		if (!table[port]) {
			err = -ENOMEM;
			goto rollback_table_setup;
		}

		err = gid_table_reserve_default(ib_dev,
						port + rdma_start_port(ib_dev),
						table[port]);
		if (err)
			goto rollback_table_setup;
	}

	ib_dev->cache.gid_cache = table;
	return 0;

rollback_table_setup:
	for (port = 0; port < ib_dev->phys_port_cnt; port++) {
		cleanup_gid_table_port(ib_dev, port + rdma_start_port(ib_dev),
				       table[port]);
		release_gid_table(table[port]);
	}

	kfree(table);
	return err;
}