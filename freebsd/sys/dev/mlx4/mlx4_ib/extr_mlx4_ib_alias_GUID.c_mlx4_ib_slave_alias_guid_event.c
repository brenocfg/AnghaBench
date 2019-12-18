#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  ag_work_lock; TYPE_2__* ports_guid; } ;
struct TYPE_8__ {TYPE_3__ alias_guid; } ;
struct mlx4_ib_dev {TYPE_4__ sriov; int /*<<< orphan*/  dev; } ;
typedef  scalar_t__ __be64 ;
struct TYPE_6__ {int state_flags; TYPE_1__* all_rec_per_port; } ;
struct TYPE_5__ {scalar_t__* guids_retry_schedule; scalar_t__ time_to_run; int /*<<< orphan*/  status; int /*<<< orphan*/  guid_indexes; int /*<<< orphan*/ * all_recs; } ;

/* Variables and functions */
 int GUID_REC_SIZE ; 
 int GUID_STATE_NEED_PORT_INIT ; 
 int /*<<< orphan*/  MLX4_GUID_FOR_DELETE_VAL ; 
 int /*<<< orphan*/  MLX4_GUID_INFO_STATUS_IDLE ; 
 scalar_t__ cpu_to_be64 (int /*<<< orphan*/ ) ; 
 scalar_t__ mlx4_get_admin_guid (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  mlx4_ib_get_aguid_comp_mask_from_ix (int) ; 
 int /*<<< orphan*/  mlx4_ib_init_alias_guid_work (struct mlx4_ib_dev*,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void mlx4_ib_slave_alias_guid_event(struct mlx4_ib_dev *dev, int slave,
				    int port,  int slave_init)
{
	__be64 curr_guid, required_guid;
	int record_num = slave / 8;
	int index = slave % 8;
	int port_index = port - 1;
	unsigned long flags;
	int do_work = 0;

	spin_lock_irqsave(&dev->sriov.alias_guid.ag_work_lock, flags);
	if (dev->sriov.alias_guid.ports_guid[port_index].state_flags &
	    GUID_STATE_NEED_PORT_INIT)
		goto unlock;
	if (!slave_init) {
		curr_guid = *(__be64 *)&dev->sriov.
			alias_guid.ports_guid[port_index].
			all_rec_per_port[record_num].
			all_recs[GUID_REC_SIZE * index];
		if (curr_guid == cpu_to_be64(MLX4_GUID_FOR_DELETE_VAL) ||
		    !curr_guid)
			goto unlock;
		required_guid = cpu_to_be64(MLX4_GUID_FOR_DELETE_VAL);
	} else {
		required_guid = mlx4_get_admin_guid(dev->dev, slave, port);
		if (required_guid == cpu_to_be64(MLX4_GUID_FOR_DELETE_VAL))
			goto unlock;
	}
	*(__be64 *)&dev->sriov.alias_guid.ports_guid[port_index].
		all_rec_per_port[record_num].
		all_recs[GUID_REC_SIZE * index] = required_guid;
	dev->sriov.alias_guid.ports_guid[port_index].
		all_rec_per_port[record_num].guid_indexes
		|= mlx4_ib_get_aguid_comp_mask_from_ix(index);
	dev->sriov.alias_guid.ports_guid[port_index].
		all_rec_per_port[record_num].status
		= MLX4_GUID_INFO_STATUS_IDLE;
	/* set to run immediately */
	dev->sriov.alias_guid.ports_guid[port_index].
		all_rec_per_port[record_num].time_to_run = 0;
	dev->sriov.alias_guid.ports_guid[port_index].
		all_rec_per_port[record_num].
		guids_retry_schedule[index] = 0;
	do_work = 1;
unlock:
	spin_unlock_irqrestore(&dev->sriov.alias_guid.ag_work_lock, flags);

	if (do_work)
		mlx4_ib_init_alias_guid_work(dev, port_index);
}