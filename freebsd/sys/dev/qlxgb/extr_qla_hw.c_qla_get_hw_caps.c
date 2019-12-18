#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  qla_host_t ;

/* Variables and functions */
 int /*<<< orphan*/  qla_get_flow_control (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qla_get_max_lro (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qla_get_max_mtu (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qla_get_max_rcv_cntxts (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qla_get_max_rds (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qla_get_max_rules (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qla_get_max_sds (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qla_get_max_tx_cntxts (int /*<<< orphan*/ *) ; 

void
qla_get_hw_caps(qla_host_t *ha)
{
	//qla_read_mac_addr(ha);
	qla_get_max_rds(ha);
	qla_get_max_sds(ha);
	qla_get_max_rules(ha);
	qla_get_max_rcv_cntxts(ha);
	qla_get_max_tx_cntxts(ha);
	qla_get_max_mtu(ha);
	qla_get_max_lro(ha);
	qla_get_flow_control(ha);
	return;
}