#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct TYPE_6__ {scalar_t__ init_tx_cnxt; } ;
struct TYPE_7__ {scalar_t__ num_tx_rings; TYPE_1__ flags; } ;
struct TYPE_8__ {TYPE_2__ hw; } ;
typedef  TYPE_3__ qla_host_t ;

/* Variables and functions */
 int qla_del_xmt_cntxt_i (TYPE_3__*,scalar_t__) ; 

__attribute__((used)) static int
qla_del_xmt_cntxt(qla_host_t *ha)
{
	uint32_t i;
	int ret = 0;

	if (!ha->hw.flags.init_tx_cnxt)
		return (ret);

	for (i = 0; i < ha->hw.num_tx_rings; i++) {
		if ((ret = qla_del_xmt_cntxt_i(ha, i)) != 0)
			break;
	}
	ha->hw.flags.init_tx_cnxt = 0;

	return (ret);
}