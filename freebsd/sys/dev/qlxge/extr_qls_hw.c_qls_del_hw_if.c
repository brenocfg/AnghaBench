#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_7__ {scalar_t__ intr_enable; } ;
struct TYPE_8__ {scalar_t__ hw_init; int num_tx_rings; int num_rx_rings; TYPE_1__ flags; } ;
typedef  TYPE_2__ qla_host_t ;

/* Variables and functions */
 int Q81_CTL_INTRE_EI ; 
 int Q81_CTL_INTRE_IHD ; 
 int Q81_CTL_INTRE_MASK_SHIFT ; 
 int /*<<< orphan*/  Q81_CTL_INTR_ENABLE ; 
 int /*<<< orphan*/  Q81_DISABLE_INTR (TYPE_2__*,int) ; 
 int /*<<< orphan*/  Q81_SET_CQ_INVALID (int) ; 
 int /*<<< orphan*/  Q81_SET_WQ_INVALID (int) ; 
 int /*<<< orphan*/  WRITE_REG32 (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  qls_hw_reset (TYPE_2__*) ; 

void
qls_del_hw_if(qla_host_t *ha)
{
	uint32_t value;
	int i;
	//int  count;

	if (ha->hw_init == 0) {
		qls_hw_reset(ha);
		return;
	}

	for (i = 0;  i < ha->num_tx_rings; i++) {
		Q81_SET_WQ_INVALID(i); 
	}
	for (i = 0;  i < ha->num_rx_rings; i++) {
		Q81_SET_CQ_INVALID(i);
	}

	for (i = 0; i < ha->num_rx_rings; i++) {
		Q81_DISABLE_INTR(ha, i); /* MSI-x i */
	}

	value = (Q81_CTL_INTRE_IHD << Q81_CTL_INTRE_MASK_SHIFT);
	WRITE_REG32(ha, Q81_CTL_INTR_ENABLE, value);

	value = (Q81_CTL_INTRE_EI << Q81_CTL_INTRE_MASK_SHIFT);
	WRITE_REG32(ha, Q81_CTL_INTR_ENABLE, value);
	ha->flags.intr_enable = 0;

	qls_hw_reset(ha);

	return;
}