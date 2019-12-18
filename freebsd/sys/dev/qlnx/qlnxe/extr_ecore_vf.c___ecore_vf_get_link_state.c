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
struct ecore_mcp_link_state {int /*<<< orphan*/  sfp_tx_fault; int /*<<< orphan*/  partner_adv_pause; int /*<<< orphan*/  partner_rx_flow_ctrl_en; int /*<<< orphan*/  partner_tx_flow_ctrl_en; int /*<<< orphan*/  partner_adv_speed; int /*<<< orphan*/  pfc_enabled; int /*<<< orphan*/  parallel_detection; int /*<<< orphan*/  an_complete; int /*<<< orphan*/  an; int /*<<< orphan*/  full_duplex; int /*<<< orphan*/  speed; int /*<<< orphan*/  link_up; } ;
struct ecore_bulletin_content {int /*<<< orphan*/  sfp_tx_fault; int /*<<< orphan*/  partner_adv_pause; int /*<<< orphan*/  partner_rx_flow_ctrl_en; int /*<<< orphan*/  partner_tx_flow_ctrl_en; int /*<<< orphan*/  partner_adv_speed; int /*<<< orphan*/  pfc_enabled; int /*<<< orphan*/  parallel_detection; int /*<<< orphan*/  autoneg_complete; int /*<<< orphan*/  autoneg; int /*<<< orphan*/  full_duplex; int /*<<< orphan*/  speed; int /*<<< orphan*/  link_up; } ;

/* Variables and functions */
 int /*<<< orphan*/  OSAL_MEMSET (struct ecore_mcp_link_state*,int /*<<< orphan*/ ,int) ; 

void __ecore_vf_get_link_state(struct ecore_mcp_link_state *p_link,
			       struct ecore_bulletin_content *p_bulletin)
{
	OSAL_MEMSET(p_link, 0, sizeof(*p_link));

	p_link->link_up = p_bulletin->link_up;
	p_link->speed = p_bulletin->speed;
	p_link->full_duplex = p_bulletin->full_duplex;
	p_link->an = p_bulletin->autoneg;
	p_link->an_complete = p_bulletin->autoneg_complete;
	p_link->parallel_detection = p_bulletin->parallel_detection;
	p_link->pfc_enabled = p_bulletin->pfc_enabled;
	p_link->partner_adv_speed = p_bulletin->partner_adv_speed;
	p_link->partner_tx_flow_ctrl_en = p_bulletin->partner_tx_flow_ctrl_en;
	p_link->partner_rx_flow_ctrl_en = p_bulletin->partner_rx_flow_ctrl_en;
	p_link->partner_adv_pause = p_bulletin->partner_adv_pause;
	p_link->sfp_tx_fault = p_bulletin->sfp_tx_fault;
}