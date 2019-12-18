#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct TYPE_12__ {scalar_t__ init_intr_cnxt; } ;
struct TYPE_11__ {scalar_t__ num_sds_rings; scalar_t__ enable_soft_lro; TYPE_2__ flags; } ;
struct TYPE_13__ {TYPE_1__ hw; } ;
typedef  TYPE_3__ qla_host_t ;

/* Variables and functions */
 scalar_t__ Q8_MAX_INTR_VECTORS ; 
 scalar_t__ qla_config_intr_cntxt (TYPE_3__*,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qla_del_rcv_cntxt (TYPE_3__*) ; 
 scalar_t__ qla_del_xmt_cntxt (TYPE_3__*) ; 
 int /*<<< orphan*/  qla_drain_soft_lro (TYPE_3__*) ; 
 int /*<<< orphan*/  qla_free_soft_lro (TYPE_3__*) ; 
 int /*<<< orphan*/  qla_stop_nic_func (TYPE_3__*) ; 

void
ql_del_hw_if(qla_host_t *ha)
{
	uint32_t i;
	uint32_t num_msix;

	(void)qla_stop_nic_func(ha);

	qla_del_rcv_cntxt(ha);

	if(qla_del_xmt_cntxt(ha))
		goto ql_del_hw_if_exit;

	if (ha->hw.flags.init_intr_cnxt) {
		for (i = 0; i < ha->hw.num_sds_rings; ) {

			if ((i + Q8_MAX_INTR_VECTORS) < ha->hw.num_sds_rings)
				num_msix = Q8_MAX_INTR_VECTORS;
			else
				num_msix = ha->hw.num_sds_rings - i;

			if (qla_config_intr_cntxt(ha, i, num_msix, 0))
				break;

			i += num_msix;
		}

		ha->hw.flags.init_intr_cnxt = 0;
	}

ql_del_hw_if_exit:
	if (ha->hw.enable_soft_lro) {
		qla_drain_soft_lro(ha);
		qla_free_soft_lro(ha);
	}

	return;
}