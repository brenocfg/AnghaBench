#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  forced_tx; int /*<<< orphan*/  forced_rx; int /*<<< orphan*/  autoneg; } ;
struct TYPE_4__ {int /*<<< orphan*/  forced_speed; int /*<<< orphan*/  advertised_speeds; int /*<<< orphan*/  autoneg; } ;
struct ecore_mcp_link_params {int /*<<< orphan*/  loopback_mode; TYPE_1__ pause; TYPE_2__ speed; } ;
struct ecore_bulletin_content {int /*<<< orphan*/  req_loopback; int /*<<< orphan*/  req_forced_tx; int /*<<< orphan*/  req_forced_rx; int /*<<< orphan*/  req_autoneg_pause; int /*<<< orphan*/  req_forced_speed; int /*<<< orphan*/  req_adv_speed; int /*<<< orphan*/  req_autoneg; } ;

/* Variables and functions */
 int /*<<< orphan*/  OSAL_MEMSET (struct ecore_mcp_link_params*,int /*<<< orphan*/ ,int) ; 

void __ecore_vf_get_link_params(struct ecore_mcp_link_params *p_params,
				struct ecore_bulletin_content *p_bulletin)
{
	OSAL_MEMSET(p_params, 0, sizeof(*p_params));

	p_params->speed.autoneg = p_bulletin->req_autoneg;
	p_params->speed.advertised_speeds = p_bulletin->req_adv_speed;
	p_params->speed.forced_speed = p_bulletin->req_forced_speed;
	p_params->pause.autoneg = p_bulletin->req_autoneg_pause;
	p_params->pause.forced_rx = p_bulletin->req_forced_rx;
	p_params->pause.forced_tx = p_bulletin->req_forced_tx;
	p_params->loopback_mode = p_bulletin->req_loopback;
}