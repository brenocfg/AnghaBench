#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_6__ {TYPE_1__* mcast; } ;
struct TYPE_7__ {TYPE_2__ hw; } ;
typedef  TYPE_3__ qla_host_t ;
struct TYPE_5__ {int /*<<< orphan*/  addr; } ;

/* Variables and functions */
 int Q8_MAX_NUM_MULTICAST_ADDRS ; 
 scalar_t__ QL_MAC_CMP (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
qla_hw_mac_addr_present(qla_host_t *ha, uint8_t *mta)
{
	int i;

	for (i = 0; i < Q8_MAX_NUM_MULTICAST_ADDRS; i++) {
		if (QL_MAC_CMP(ha->hw.mcast[i].addr, mta) == 0)
			return (0); /* its been already added */
	}
	return (-1);
}