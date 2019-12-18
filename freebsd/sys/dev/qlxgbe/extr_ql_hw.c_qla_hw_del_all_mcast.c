#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  qla_mcast_t ;
struct TYPE_5__ {scalar_t__ nmcast; int /*<<< orphan*/  mcast; } ;
struct TYPE_6__ {TYPE_1__ hw; } ;
typedef  TYPE_2__ qla_host_t ;

/* Variables and functions */
 int Q8_MAX_NUM_MULTICAST_ADDRS ; 
 int /*<<< orphan*/  bzero (int /*<<< orphan*/ ,int) ; 
 int qla_hw_all_mcast (TYPE_2__*,int /*<<< orphan*/ ) ; 

int
qla_hw_del_all_mcast(qla_host_t *ha)
{
	int ret;

	ret = qla_hw_all_mcast(ha, 0);

	bzero(ha->hw.mcast, (sizeof (qla_mcast_t) * Q8_MAX_NUM_MULTICAST_ADDRS));
	ha->hw.nmcast = 0;

	return (ret);
}