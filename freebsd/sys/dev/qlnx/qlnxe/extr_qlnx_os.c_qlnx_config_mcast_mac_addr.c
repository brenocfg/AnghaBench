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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ uint32_t ;
struct ecore_filter_mcast {int num_mc_addrs; int /*<<< orphan*/  mac; int /*<<< orphan*/  opcode; } ;
struct ecore_dev {int dummy; } ;
struct TYPE_3__ {struct ecore_filter_mcast ecore_mcast; struct ecore_dev cdev; } ;
typedef  TYPE_1__ qlnx_host_t ;

/* Variables and functions */
 int /*<<< orphan*/  ECORE_FILTER_ADD ; 
 int /*<<< orphan*/  ECORE_FILTER_REMOVE ; 
 int /*<<< orphan*/  ECORE_SPQ_MODE_CB ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  bzero (struct ecore_filter_mcast*,int) ; 
 int ecore_filter_mcast_cmd (struct ecore_dev*,struct ecore_filter_mcast*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
qlnx_config_mcast_mac_addr(qlnx_host_t *ha, uint8_t *mac_addr, uint32_t add_mac)
{
	struct ecore_filter_mcast	*mcast;
	struct ecore_dev		*cdev;
	int				rc;

	cdev = &ha->cdev;

	mcast = &ha->ecore_mcast;
	bzero(mcast, sizeof(struct ecore_filter_mcast));

	if (add_mac)
		mcast->opcode = ECORE_FILTER_ADD;
	else
		mcast->opcode = ECORE_FILTER_REMOVE;

	mcast->num_mc_addrs = 1;
	memcpy(mcast->mac, mac_addr, ETH_ALEN);

	rc = ecore_filter_mcast_cmd(cdev, mcast, ECORE_SPQ_MODE_CB, NULL);

	return (rc);
}