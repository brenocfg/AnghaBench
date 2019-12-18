#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {TYPE_3__* ports_guid; } ;
struct TYPE_12__ {TYPE_4__ alias_guid; } ;
struct mlx4_ib_dev {TYPE_5__ sriov; TYPE_6__* dev; } ;
typedef  int /*<<< orphan*/  __be64 ;
struct TYPE_13__ {TYPE_1__* persist; } ;
struct TYPE_10__ {TYPE_2__* all_rec_per_port; } ;
struct TYPE_9__ {int /*<<< orphan*/ * all_recs; } ;
struct TYPE_8__ {int num_vfs; } ;

/* Variables and functions */
 int GUID_REC_SIZE ; 
 int NUM_ALIAS_GUID_IN_REC ; 
 int NUM_ALIAS_GUID_REC_IN_PORT ; 
 scalar_t__ be64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx4_get_admin_guid (TYPE_6__*,int,int) ; 
 int /*<<< orphan*/  mlx4_is_slave_active (TYPE_6__*,int) ; 
 int /*<<< orphan*/  pr_debug (char*,int,long long,int) ; 

__attribute__((used)) static void mlx4_ib_guid_port_init(struct mlx4_ib_dev *dev, int port)
{
	int j, k, entry;
	__be64 guid;

	/*Check if the SM doesn't need to assign the GUIDs*/
	for (j = 0; j < NUM_ALIAS_GUID_REC_IN_PORT; j++) {
		for (k = 0; k < NUM_ALIAS_GUID_IN_REC; k++) {
			entry = j * NUM_ALIAS_GUID_IN_REC + k;
			/* no request for the 0 entry (hw guid) */
			if (!entry || entry > dev->dev->persist->num_vfs ||
			    !mlx4_is_slave_active(dev->dev, entry))
				continue;
			guid = mlx4_get_admin_guid(dev->dev, entry, port);
			*(__be64 *)&dev->sriov.alias_guid.ports_guid[port - 1].
				all_rec_per_port[j].all_recs
				[GUID_REC_SIZE * k] = guid;
			pr_debug("guid was set, entry=%d, val=0x%llx, port=%d\n",
				 entry,
				 (long long)be64_to_cpu(guid),
				 port);
		}
	}
}