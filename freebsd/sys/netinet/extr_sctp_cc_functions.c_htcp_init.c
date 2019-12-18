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
struct TYPE_4__ {int /*<<< orphan*/  last_cong; int /*<<< orphan*/  bytes_acked; int /*<<< orphan*/  beta; int /*<<< orphan*/  alpha; } ;
struct TYPE_3__ {TYPE_2__ htcp_ca; } ;
struct sctp_nets {TYPE_1__ cc_mod; int /*<<< orphan*/  mtu; } ;
struct htcp {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALPHA_BASE ; 
 int /*<<< orphan*/  BETA_MIN ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sctp_get_tick_count () ; 

__attribute__((used)) static void
htcp_init(struct sctp_nets *net)
{
	memset(&net->cc_mod.htcp_ca, 0, sizeof(struct htcp));
	net->cc_mod.htcp_ca.alpha = ALPHA_BASE;
	net->cc_mod.htcp_ca.beta = BETA_MIN;
	net->cc_mod.htcp_ca.bytes_acked = net->mtu;
	net->cc_mod.htcp_ca.last_cong = sctp_get_tick_count();
}