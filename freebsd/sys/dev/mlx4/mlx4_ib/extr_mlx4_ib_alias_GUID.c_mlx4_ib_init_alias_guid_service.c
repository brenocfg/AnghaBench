#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  union ib_gid {int dummy; } ib_gid ;
struct mlx4_sriov_alias_guid_port_rec_det {int dummy; } ;
struct TYPE_7__ {int /*<<< orphan*/ * sa_client; TYPE_5__* ports_guid; int /*<<< orphan*/  ag_work_lock; } ;
struct TYPE_8__ {TYPE_2__ alias_guid; } ;
struct TYPE_9__ {scalar_t__ (* query_gid ) (TYPE_4__*,int,int /*<<< orphan*/ ,union ib_gid*) ;} ;
struct mlx4_ib_dev {int num_ports; TYPE_3__ sriov; int /*<<< orphan*/  dev; TYPE_4__ ib_dev; } ;
struct TYPE_10__ {int port; int /*<<< orphan*/ * wq; int /*<<< orphan*/  alias_guid_work; TYPE_2__* parent; int /*<<< orphan*/  cb_list; TYPE_1__* all_rec_per_port; int /*<<< orphan*/  state_flags; } ;
struct TYPE_6__ {TYPE_5__* all_recs; } ;

/* Variables and functions */
 int EFAULT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  GUID_STATE_NEED_PORT_INIT ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int NUM_ALIAS_GUID_PER_PORT ; 
 int NUM_ALIAS_GUID_REC_IN_PORT ; 
 int /*<<< orphan*/  WQ_MEM_RECLAIM ; 
 int /*<<< orphan*/  alias_guid_work ; 
 int /*<<< orphan*/ * alloc_ordered_workqueue (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  destroy_workqueue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ib_sa_register_client (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ib_sa_unregister_client (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  invalidate_guid_record (struct mlx4_ib_dev*,int,int) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_5__*,int,int) ; 
 scalar_t__ mlx4_ib_sm_guid_assign ; 
 int /*<<< orphan*/  mlx4_is_master (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx4_set_admin_guid (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 scalar_t__ stub1 (TYPE_4__*,int,int /*<<< orphan*/ ,union ib_gid*) ; 

int mlx4_ib_init_alias_guid_service(struct mlx4_ib_dev *dev)
{
	char alias_wq_name[15];
	int ret = 0;
	int i, j;
	union ib_gid gid;

	if (!mlx4_is_master(dev->dev))
		return 0;
	dev->sriov.alias_guid.sa_client =
		kzalloc(sizeof *dev->sriov.alias_guid.sa_client, GFP_KERNEL);
	if (!dev->sriov.alias_guid.sa_client)
		return -ENOMEM;

	ib_sa_register_client(dev->sriov.alias_guid.sa_client);

	spin_lock_init(&dev->sriov.alias_guid.ag_work_lock);

	for (i = 1; i <= dev->num_ports; ++i) {
		if (dev->ib_dev.query_gid(&dev->ib_dev , i, 0, &gid)) {
			ret = -EFAULT;
			goto err_unregister;
		}
	}

	for (i = 0 ; i < dev->num_ports; i++) {
		memset(&dev->sriov.alias_guid.ports_guid[i], 0,
		       sizeof (struct mlx4_sriov_alias_guid_port_rec_det));
		dev->sriov.alias_guid.ports_guid[i].state_flags |=
				GUID_STATE_NEED_PORT_INIT;
		for (j = 0; j < NUM_ALIAS_GUID_REC_IN_PORT; j++) {
			/* mark each val as it was deleted */
			memset(dev->sriov.alias_guid.ports_guid[i].
				all_rec_per_port[j].all_recs, 0xFF,
				sizeof(dev->sriov.alias_guid.ports_guid[i].
				all_rec_per_port[j].all_recs));
		}
		INIT_LIST_HEAD(&dev->sriov.alias_guid.ports_guid[i].cb_list);
		/*prepare the records, set them to be allocated by sm*/
		if (mlx4_ib_sm_guid_assign)
			for (j = 1; j < NUM_ALIAS_GUID_PER_PORT; j++)
				mlx4_set_admin_guid(dev->dev, 0, j, i + 1);
		for (j = 0 ; j < NUM_ALIAS_GUID_REC_IN_PORT; j++)
			invalidate_guid_record(dev, i + 1, j);

		dev->sriov.alias_guid.ports_guid[i].parent = &dev->sriov.alias_guid;
		dev->sriov.alias_guid.ports_guid[i].port  = i;

		snprintf(alias_wq_name, sizeof alias_wq_name, "alias_guid%d", i);
		dev->sriov.alias_guid.ports_guid[i].wq =
			alloc_ordered_workqueue(alias_wq_name, WQ_MEM_RECLAIM);
		if (!dev->sriov.alias_guid.ports_guid[i].wq) {
			ret = -ENOMEM;
			goto err_thread;
		}
		INIT_DELAYED_WORK(&dev->sriov.alias_guid.ports_guid[i].alias_guid_work,
			  alias_guid_work);
	}
	return 0;

err_thread:
	for (--i; i >= 0; i--) {
		destroy_workqueue(dev->sriov.alias_guid.ports_guid[i].wq);
		dev->sriov.alias_guid.ports_guid[i].wq = NULL;
	}

err_unregister:
	ib_sa_unregister_client(dev->sriov.alias_guid.sa_client);
	kfree(dev->sriov.alias_guid.sa_client);
	dev->sriov.alias_guid.sa_client = NULL;
	pr_err("init_alias_guid_service: Failed. (ret:%d)\n", ret);
	return ret;
}