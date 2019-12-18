#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
struct TYPE_7__ {TYPE_4__* rx_cntxt_rsp; } ;
struct TYPE_9__ {TYPE_1__ hw; } ;
typedef  TYPE_3__ qla_host_t ;
struct TYPE_8__ {int /*<<< orphan*/  cntxt_id; } ;
struct TYPE_10__ {TYPE_2__ rx_rsp; } ;
typedef  TYPE_4__ q80_rcv_cntxt_rsp_t ;

/* Variables and functions */
 int /*<<< orphan*/  Q8_MAC_ADDR_LEN ; 
 int /*<<< orphan*/  qla_config_mac_addr (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

void
qla_hw_set_multi(qla_host_t *ha, uint8_t *mta, uint32_t mcnt,
	uint32_t add_multi)
{
	q80_rcv_cntxt_rsp_t	*rsp;
	int i;

	rsp = ha->hw.rx_cntxt_rsp;
	for (i = 0; i < mcnt; i++) {
		qla_config_mac_addr(ha, mta, rsp->rx_rsp.cntxt_id, add_multi);
		mta += Q8_MAC_ADDR_LEN;
	}
	return;
}