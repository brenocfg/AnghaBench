#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ecore_filter_mcast {int /*<<< orphan*/  num_mc_addrs; scalar_t__* addr; int /*<<< orphan*/ ** mac; int /*<<< orphan*/  opcode; } ;
struct ecore_dev {int dummy; } ;
typedef  int /*<<< orphan*/  qlnx_mcast_t ;
struct TYPE_3__ {scalar_t__ nmcast; struct ecore_filter_mcast* mcast; struct ecore_filter_mcast ecore_mcast; struct ecore_dev cdev; } ;
typedef  TYPE_1__ qlnx_host_t ;

/* Variables and functions */
 int /*<<< orphan*/  ECORE_FILTER_REMOVE ; 
 int /*<<< orphan*/  ECORE_SPQ_MODE_CB ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 int QLNX_MAX_NUM_MULTICAST_ADDRS ; 
 int /*<<< orphan*/  bzero (struct ecore_filter_mcast*,int) ; 
 int ecore_filter_mcast_cmd (struct ecore_dev*,struct ecore_filter_mcast*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,scalar_t__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
qlnx_remove_all_mcast_mac(qlnx_host_t *ha)
{
	struct ecore_filter_mcast	*mcast;
	struct ecore_dev		*cdev;
	int				rc, i;

	cdev = &ha->cdev;

	mcast = &ha->ecore_mcast;
	bzero(mcast, sizeof(struct ecore_filter_mcast));

	mcast->opcode = ECORE_FILTER_REMOVE;

	for (i = 0; i < QLNX_MAX_NUM_MULTICAST_ADDRS; i++) {

		if (ha->mcast[i].addr[0] || ha->mcast[i].addr[1] ||
			ha->mcast[i].addr[2] || ha->mcast[i].addr[3] ||
			ha->mcast[i].addr[4] || ha->mcast[i].addr[5]) {

			memcpy(&mcast->mac[i][0], &ha->mcast[i].addr[0], ETH_ALEN);
			mcast->num_mc_addrs++;
		}
	}
	mcast = &ha->ecore_mcast;

	rc = ecore_filter_mcast_cmd(cdev, mcast, ECORE_SPQ_MODE_CB, NULL);

	bzero(ha->mcast, (sizeof(qlnx_mcast_t) * QLNX_MAX_NUM_MULTICAST_ADDRS));
	ha->nmcast = 0;

	return (rc);
}