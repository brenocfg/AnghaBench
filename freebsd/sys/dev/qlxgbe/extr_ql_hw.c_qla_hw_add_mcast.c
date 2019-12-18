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
typedef  scalar_t__ uint32_t ;
struct TYPE_6__ {int /*<<< orphan*/  nmcast; TYPE_1__* mcast; } ;
struct TYPE_7__ {TYPE_2__ hw; } ;
typedef  TYPE_3__ qla_host_t ;
struct TYPE_5__ {scalar_t__* addr; } ;

/* Variables and functions */
 int ETHER_ADDR_LEN ; 
 int /*<<< orphan*/  Q8_MAC_ADDR_LEN ; 
 int Q8_MAX_NUM_MULTICAST_ADDRS ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ *,scalar_t__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
qla_hw_add_mcast(qla_host_t *ha, uint8_t *mta, uint32_t nmcast)
{
	int i;

	for (i = 0; i < Q8_MAX_NUM_MULTICAST_ADDRS; i++) {

		if ((ha->hw.mcast[i].addr[0] == 0) && 
			(ha->hw.mcast[i].addr[1] == 0) &&
			(ha->hw.mcast[i].addr[2] == 0) &&
			(ha->hw.mcast[i].addr[3] == 0) &&
			(ha->hw.mcast[i].addr[4] == 0) &&
			(ha->hw.mcast[i].addr[5] == 0)) {

			bcopy(mta, ha->hw.mcast[i].addr, Q8_MAC_ADDR_LEN);
			ha->hw.nmcast++;	

			mta = mta + ETHER_ADDR_LEN;
			nmcast--;

			if (nmcast == 0)
				break;
		}

	}
	return 0;
}