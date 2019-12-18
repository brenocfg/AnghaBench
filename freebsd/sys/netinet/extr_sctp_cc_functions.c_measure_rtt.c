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
typedef  scalar_t__ uint32_t ;
struct TYPE_4__ {scalar_t__ minRTT; scalar_t__ maxRTT; } ;
struct TYPE_3__ {TYPE_2__ htcp_ca; } ;
struct sctp_nets {scalar_t__ lastsa; scalar_t__ fast_retran_ip; int ssthresh; TYPE_1__ cc_mod; } ;

/* Variables and functions */
 scalar_t__ MSEC_TO_TICKS (int) ; 
 scalar_t__ SCTP_RTT_SHIFT ; 
 int htcp_ccount (TYPE_2__*) ; 

__attribute__((used)) static inline void
measure_rtt(struct sctp_nets *net)
{
	uint32_t srtt = net->lastsa >> SCTP_RTT_SHIFT;

	/* keep track of minimum RTT seen so far, minRTT is zero at first */
	if (net->cc_mod.htcp_ca.minRTT > srtt || !net->cc_mod.htcp_ca.minRTT)
		net->cc_mod.htcp_ca.minRTT = srtt;

	/* max RTT */
	if (net->fast_retran_ip == 0 && net->ssthresh < 0xFFFF && htcp_ccount(&net->cc_mod.htcp_ca) > 3) {
		if (net->cc_mod.htcp_ca.maxRTT < net->cc_mod.htcp_ca.minRTT)
			net->cc_mod.htcp_ca.maxRTT = net->cc_mod.htcp_ca.minRTT;
		if (net->cc_mod.htcp_ca.maxRTT < srtt && srtt <= net->cc_mod.htcp_ca.maxRTT + MSEC_TO_TICKS(20))
			net->cc_mod.htcp_ca.maxRTT = srtt;
	}
}