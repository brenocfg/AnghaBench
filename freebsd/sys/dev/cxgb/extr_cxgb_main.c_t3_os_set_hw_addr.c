#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_5__ {TYPE_1__* port; } ;
typedef  TYPE_2__ adapter_t ;
struct TYPE_4__ {int /*<<< orphan*/  hw_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETHER_ADDR_LEN ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ cxgb_debug ; 
 int /*<<< orphan*/  printf (char*,int,int /*<<< orphan*/ *,char*) ; 

void
t3_os_set_hw_addr(adapter_t *adapter, int port_idx, u8 hw_addr[])
{

	/*
	 * The ifnet might not be allocated before this gets called,
	 * as this is called early on in attach by t3_prep_adapter
	 * save the address off in the port structure
	 */
	if (cxgb_debug)
		printf("set_hw_addr on idx %d addr %6D\n", port_idx, hw_addr, ":");
	bcopy(hw_addr, adapter->port[port_idx].hw_addr, ETHER_ADDR_LEN);
}