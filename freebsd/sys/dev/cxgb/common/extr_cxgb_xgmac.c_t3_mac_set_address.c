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
typedef  int /*<<< orphan*/  u8 ;
struct cmac {unsigned int ext_port; unsigned int nucast; TYPE_2__* adapter; scalar_t__ multiport; } ;
struct TYPE_3__ {unsigned int nports; } ;
struct TYPE_4__ {TYPE_1__ params; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  set_addr_filter (struct cmac*,unsigned int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  t3_vsc7323_set_addr (TYPE_2__*,int /*<<< orphan*/ *,unsigned int) ; 

int t3_mac_set_address(struct cmac *mac, unsigned int idx, u8 addr[6])
{
	if (mac->multiport)
		idx = mac->ext_port + idx * mac->adapter->params.nports;
	if (idx >= mac->nucast)
		return -EINVAL;
	set_addr_filter(mac, idx, addr);
	if (mac->multiport && idx < mac->adapter->params.nports)
		t3_vsc7323_set_addr(mac->adapter, addr, idx);
	return 0;
}