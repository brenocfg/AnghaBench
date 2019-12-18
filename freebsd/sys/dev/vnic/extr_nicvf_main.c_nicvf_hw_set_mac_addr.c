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
struct TYPE_2__ {int /*<<< orphan*/  mac_addr; int /*<<< orphan*/  vf_id; int /*<<< orphan*/  msg; } ;
union nic_mbx {TYPE_1__ mac; } ;
typedef  int /*<<< orphan*/  uint8_t ;
struct nicvf {int /*<<< orphan*/  vf_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETHER_ADDR_LEN ; 
 int /*<<< orphan*/  NIC_MBOX_MSG_SET_MAC ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int nicvf_send_msg_to_pf (struct nicvf*,union nic_mbx*) ; 

__attribute__((used)) static int
nicvf_hw_set_mac_addr(struct nicvf *nic, uint8_t *hwaddr)
{
	union nic_mbx mbx = {};

	mbx.mac.msg = NIC_MBOX_MSG_SET_MAC;
	mbx.mac.vf_id = nic->vf_id;
	memcpy(mbx.mac.mac_addr, hwaddr, ETHER_ADDR_LEN);

	return (nicvf_send_msg_to_pf(nic, &mbx));
}