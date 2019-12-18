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
typedef  int uint64_t ;
typedef  int uint32_t ;
struct timeval {scalar_t__ tv_sec; scalar_t__ tv_usec; } ;
struct TYPE_4__ {int sat_network_lockout; int sat_network; int minrto; int maxrto; scalar_t__ use_precise_time; } ;
struct sctp_tcb {TYPE_2__ asoc; } ;
struct sctp_nets {int rtt; scalar_t__ lan_type; int RTO_measured; int lastsa; int lastsv; int RTO; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* sctp_rtt_calculated ) (struct sctp_tcb*,struct sctp_nets*,struct timeval*) ;} ;
struct sctp_association {TYPE_1__ cc_functions; } ;
typedef  int int32_t ;

/* Variables and functions */
 int SCTP_BASE_SYSCTL (int /*<<< orphan*/ ) ; 
 int SCTP_CLOCK_GRANULARITY ; 
 int /*<<< orphan*/  SCTP_GETPTIME_TIMEVAL (struct timeval*) ; 
 int /*<<< orphan*/  SCTP_GETTIME_TIMEVAL (struct timeval*) ; 
 scalar_t__ SCTP_LAN_INTERNET ; 
 scalar_t__ SCTP_LAN_LOCAL ; 
 scalar_t__ SCTP_LAN_UNKNOWN ; 
 int SCTP_LOCAL_LAN_RTT ; 
 int /*<<< orphan*/  SCTP_LOG_INITIAL_RTT ; 
 int /*<<< orphan*/  SCTP_LOG_RTTVAR ; 
 int SCTP_RTO_UPPER_BOUND ; 
 int SCTP_RTTVAR_LOGGING_ENABLE ; 
 int SCTP_RTT_FROM_DATA ; 
 int SCTP_RTT_SHIFT ; 
 int SCTP_RTT_VAR_SHIFT ; 
 int SCTP_SAT_NETWORK_MIN ; 
 int /*<<< orphan*/  rto_logging (struct sctp_nets*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sctp_logging_level ; 
 int /*<<< orphan*/  stub1 (struct sctp_tcb*,struct sctp_nets*,struct timeval*) ; 
 int /*<<< orphan*/  timevalsub (struct timeval*,struct timeval*) ; 

int
sctp_calculate_rto(struct sctp_tcb *stcb,
    struct sctp_association *asoc,
    struct sctp_nets *net,
    struct timeval *old,
    int rtt_from_sack)
{
	struct timeval now;
	uint64_t rtt_us;	/* RTT in us */
	int32_t rtt;		/* RTT in ms */
	uint32_t new_rto;
	int first_measure = 0;

	/************************/
	/* 1. calculate new RTT */
	/************************/
	/* get the current time */
	if (stcb->asoc.use_precise_time) {
		(void)SCTP_GETPTIME_TIMEVAL(&now);
	} else {
		(void)SCTP_GETTIME_TIMEVAL(&now);
	}
	if ((old->tv_sec > now.tv_sec) ||
	    ((old->tv_sec == now.tv_sec) && (old->tv_sec > now.tv_sec))) {
		/* The starting point is in the future. */
		return (0);
	}
	timevalsub(&now, old);
	rtt_us = (uint64_t)1000000 * (uint64_t)now.tv_sec + (uint64_t)now.tv_usec;
	if (rtt_us > SCTP_RTO_UPPER_BOUND * 1000) {
		/* The RTT is larger than a sane value. */
		return (0);
	}
	/* store the current RTT in us */
	net->rtt = rtt_us;
	/* compute rtt in ms */
	rtt = (int32_t)(net->rtt / 1000);
	if ((asoc->cc_functions.sctp_rtt_calculated) && (rtt_from_sack == SCTP_RTT_FROM_DATA)) {
		/*
		 * Tell the CC module that a new update has just occurred
		 * from a sack
		 */
		(*asoc->cc_functions.sctp_rtt_calculated) (stcb, net, &now);
	}
	/*
	 * Do we need to determine the lan? We do this only on sacks i.e.
	 * RTT being determined from data not non-data (HB/INIT->INITACK).
	 */
	if ((rtt_from_sack == SCTP_RTT_FROM_DATA) &&
	    (net->lan_type == SCTP_LAN_UNKNOWN)) {
		if (net->rtt > SCTP_LOCAL_LAN_RTT) {
			net->lan_type = SCTP_LAN_INTERNET;
		} else {
			net->lan_type = SCTP_LAN_LOCAL;
		}
	}

	/***************************/
	/* 2. update RTTVAR & SRTT */
	/***************************/
	/*-
	 * Compute the scaled average lastsa and the
	 * scaled variance lastsv as described in van Jacobson
	 * Paper "Congestion Avoidance and Control", Annex A.
	 *
	 * (net->lastsa >> SCTP_RTT_SHIFT) is the srtt
	 * (net->lastsv >> SCTP_RTT_VAR_SHIFT) is the rttvar
	 */
	if (net->RTO_measured) {
		rtt -= (net->lastsa >> SCTP_RTT_SHIFT);
		net->lastsa += rtt;
		if (rtt < 0) {
			rtt = -rtt;
		}
		rtt -= (net->lastsv >> SCTP_RTT_VAR_SHIFT);
		net->lastsv += rtt;
		if (SCTP_BASE_SYSCTL(sctp_logging_level) & SCTP_RTTVAR_LOGGING_ENABLE) {
			rto_logging(net, SCTP_LOG_RTTVAR);
		}
	} else {
		/* First RTO measurment */
		net->RTO_measured = 1;
		first_measure = 1;
		net->lastsa = rtt << SCTP_RTT_SHIFT;
		net->lastsv = (rtt / 2) << SCTP_RTT_VAR_SHIFT;
		if (SCTP_BASE_SYSCTL(sctp_logging_level) & SCTP_RTTVAR_LOGGING_ENABLE) {
			rto_logging(net, SCTP_LOG_INITIAL_RTT);
		}
	}
	if (net->lastsv == 0) {
		net->lastsv = SCTP_CLOCK_GRANULARITY;
	}
	new_rto = (net->lastsa >> SCTP_RTT_SHIFT) + net->lastsv;
	if ((new_rto > SCTP_SAT_NETWORK_MIN) &&
	    (stcb->asoc.sat_network_lockout == 0)) {
		stcb->asoc.sat_network = 1;
	} else if ((!first_measure) && stcb->asoc.sat_network) {
		stcb->asoc.sat_network = 0;
		stcb->asoc.sat_network_lockout = 1;
	}
	/* bound it, per C6/C7 in Section 5.3.1 */
	if (new_rto < stcb->asoc.minrto) {
		new_rto = stcb->asoc.minrto;
	}
	if (new_rto > stcb->asoc.maxrto) {
		new_rto = stcb->asoc.maxrto;
	}
	net->RTO = new_rto;
	return (1);
}