#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ lro; } ;
struct TYPE_9__ {int num_sds_rings; TYPE_1__ flags; } ;
struct TYPE_10__ {TYPE_2__ hw; } ;
typedef  TYPE_3__ qla_host_t ;

/* Variables and functions */
 int /*<<< orphan*/  QL_DISABLE_INTERRUPTS (TYPE_3__*,int) ; 
 int /*<<< orphan*/  qla_del_rcv_cntxt (TYPE_3__*) ; 
 int /*<<< orphan*/  qla_del_xmt_cntxt (TYPE_3__*) ; 

void
qla_del_hw_if(qla_host_t *ha)
{
	int	i;

	for (i = 0; i < ha->hw.num_sds_rings; i++)
		QL_DISABLE_INTERRUPTS(ha, i);
	
	qla_del_rcv_cntxt(ha);
	qla_del_xmt_cntxt(ha);
	
	ha->hw.flags.lro = 0;
}