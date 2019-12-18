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
typedef  int uint32_t ;
struct TYPE_4__ {int bytecount; int lasttime; int alpha; int minRTT; int minB; int maxB; int Bi; scalar_t__ bytes_acked; } ;
struct TYPE_3__ {TYPE_2__ htcp_ca; } ;
struct sctp_nets {int fast_retran_ip; int cwnd; int mtu; TYPE_1__ cc_mod; scalar_t__ net_ack; } ;

/* Variables and functions */
 int htcp_ccount (TYPE_2__*) ; 
 int hz ; 
 int sctp_get_tick_count () ; 
 int /*<<< orphan*/  use_bandwidth_switch ; 

__attribute__((used)) static void
measure_achieved_throughput(struct sctp_nets *net)
{
	uint32_t now = sctp_get_tick_count();

	if (net->fast_retran_ip == 0)
		net->cc_mod.htcp_ca.bytes_acked = net->net_ack;

	if (!use_bandwidth_switch)
		return;

	/* achieved throughput calculations */
	/* JRS - not 100% sure of this statement */
	if (net->fast_retran_ip == 1) {
		net->cc_mod.htcp_ca.bytecount = 0;
		net->cc_mod.htcp_ca.lasttime = now;
		return;
	}

	net->cc_mod.htcp_ca.bytecount += net->net_ack;
	if ((net->cc_mod.htcp_ca.bytecount >= net->cwnd - (((net->cc_mod.htcp_ca.alpha >> 7) ? (net->cc_mod.htcp_ca.alpha >> 7) : 1) * net->mtu)) &&
	    (now - net->cc_mod.htcp_ca.lasttime >= net->cc_mod.htcp_ca.minRTT) &&
	    (net->cc_mod.htcp_ca.minRTT > 0)) {
		uint32_t cur_Bi = net->cc_mod.htcp_ca.bytecount / net->mtu * hz / (now - net->cc_mod.htcp_ca.lasttime);

		if (htcp_ccount(&net->cc_mod.htcp_ca) <= 3) {
			/* just after backoff */
			net->cc_mod.htcp_ca.minB = net->cc_mod.htcp_ca.maxB = net->cc_mod.htcp_ca.Bi = cur_Bi;
		} else {
			net->cc_mod.htcp_ca.Bi = (3 * net->cc_mod.htcp_ca.Bi + cur_Bi) / 4;
			if (net->cc_mod.htcp_ca.Bi > net->cc_mod.htcp_ca.maxB)
				net->cc_mod.htcp_ca.maxB = net->cc_mod.htcp_ca.Bi;
			if (net->cc_mod.htcp_ca.minB > net->cc_mod.htcp_ca.maxB)
				net->cc_mod.htcp_ca.minB = net->cc_mod.htcp_ca.maxB;
		}
		net->cc_mod.htcp_ca.bytecount = 0;
		net->cc_mod.htcp_ca.lasttime = now;
	}
}