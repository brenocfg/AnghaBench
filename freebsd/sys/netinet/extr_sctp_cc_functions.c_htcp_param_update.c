#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct TYPE_5__ {scalar_t__ minRTT; scalar_t__ maxRTT; } ;
struct TYPE_4__ {TYPE_2__ htcp_ca; } ;
struct sctp_nets {TYPE_1__ cc_mod; } ;

/* Variables and functions */
 int /*<<< orphan*/  htcp_alpha_update (TYPE_2__*) ; 
 int /*<<< orphan*/  htcp_beta_update (TYPE_2__*,scalar_t__,scalar_t__) ; 

__attribute__((used)) static void
htcp_param_update(struct sctp_nets *net)
{
	uint32_t minRTT = net->cc_mod.htcp_ca.minRTT;
	uint32_t maxRTT = net->cc_mod.htcp_ca.maxRTT;

	htcp_beta_update(&net->cc_mod.htcp_ca, minRTT, maxRTT);
	htcp_alpha_update(&net->cc_mod.htcp_ca);

	/*
	 * add slowly fading memory for maxRTT to accommodate routing
	 * changes etc
	 */
	if (minRTT > 0 && maxRTT > minRTT)
		net->cc_mod.htcp_ca.maxRTT = minRTT + ((maxRTT - minRTT) * 95) / 100;
}