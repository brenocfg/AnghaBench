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
typedef  int /*<<< orphan*/  u8 ;
struct ib_gid_table {int sz; int /*<<< orphan*/  rwlock; TYPE_1__* data_vec; } ;
struct ib_device {int dummy; } ;
struct TYPE_2__ {int props; int /*<<< orphan*/  gid; } ;

/* Variables and functions */
 int GID_ATTR_FIND_MASK_DEFAULT ; 
 int /*<<< orphan*/  del_gid (struct ib_device*,int /*<<< orphan*/ ,struct ib_gid_table*,int,int) ; 
 int /*<<< orphan*/  dispatch_gid_change_event (struct ib_device*,int /*<<< orphan*/ ) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  write_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zgid ; 

__attribute__((used)) static void cleanup_gid_table_port(struct ib_device *ib_dev, u8 port,
				   struct ib_gid_table *table)
{
	int i;
	bool deleted = false;

	if (!table)
		return;

	write_lock_irq(&table->rwlock);
	for (i = 0; i < table->sz; ++i) {
		if (memcmp(&table->data_vec[i].gid, &zgid,
			   sizeof(table->data_vec[i].gid)))
			if (!del_gid(ib_dev, port, table, i,
				     table->data_vec[i].props &
				     GID_ATTR_FIND_MASK_DEFAULT))
				deleted = true;
	}
	write_unlock_irq(&table->rwlock);

	if (deleted)
		dispatch_gid_change_event(ib_dev, port);
}