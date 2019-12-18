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
struct in_conninfo {int dummy; } ;
struct hc_metrics_lite {scalar_t__ rmx_rtt; scalar_t__ rmx_rttvar; int rmx_ssthresh; scalar_t__ rmx_cwnd; scalar_t__ rmx_sendpipe; scalar_t__ rmx_recvpipe; } ;
struct hc_metrics {scalar_t__ rmx_rtt; scalar_t__ rmx_rttvar; int rmx_ssthresh; scalar_t__ rmx_cwnd; scalar_t__ rmx_sendpipe; scalar_t__ rmx_recvpipe; TYPE_1__* rmx_head; int /*<<< orphan*/  rmx_expire; int /*<<< orphan*/  rmx_updates; } ;
struct TYPE_4__ {int /*<<< orphan*/  expire; } ;
struct TYPE_3__ {int /*<<< orphan*/  hch_mtx; int /*<<< orphan*/  hch_bucket; } ;

/* Variables and functions */
 int /*<<< orphan*/  TAILQ_INSERT_HEAD (int /*<<< orphan*/ *,struct hc_metrics*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct hc_metrics*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TCPSTAT_INC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  THC_UNLOCK (int /*<<< orphan*/ *) ; 
 TYPE_2__ V_tcp_hostcache ; 
 int /*<<< orphan*/  V_tcp_use_hostcache ; 
 int /*<<< orphan*/  rmx_q ; 
 struct hc_metrics* tcp_hc_insert (struct in_conninfo*) ; 
 struct hc_metrics* tcp_hc_lookup (struct in_conninfo*) ; 
 int /*<<< orphan*/  tcps_cachedrtt ; 
 int /*<<< orphan*/  tcps_cachedrttvar ; 
 int /*<<< orphan*/  tcps_cachedssthresh ; 

void
tcp_hc_update(struct in_conninfo *inc, struct hc_metrics_lite *hcml)
{
	struct hc_metrics *hc_entry;

	if (!V_tcp_use_hostcache)
		return;

	hc_entry = tcp_hc_lookup(inc);
	if (hc_entry == NULL) {
		hc_entry = tcp_hc_insert(inc);
		if (hc_entry == NULL)
			return;
	}
	hc_entry->rmx_updates++;
	hc_entry->rmx_expire = V_tcp_hostcache.expire; /* start over again */

	if (hcml->rmx_rtt != 0) {
		if (hc_entry->rmx_rtt == 0)
			hc_entry->rmx_rtt = hcml->rmx_rtt;
		else
			hc_entry->rmx_rtt = ((uint64_t)hc_entry->rmx_rtt +
			    (uint64_t)hcml->rmx_rtt) / 2;
		TCPSTAT_INC(tcps_cachedrtt);
	}
	if (hcml->rmx_rttvar != 0) {
	        if (hc_entry->rmx_rttvar == 0)
			hc_entry->rmx_rttvar = hcml->rmx_rttvar;
		else
			hc_entry->rmx_rttvar = ((uint64_t)hc_entry->rmx_rttvar +
			    (uint64_t)hcml->rmx_rttvar) / 2;
		TCPSTAT_INC(tcps_cachedrttvar);
	}
	if (hcml->rmx_ssthresh != 0) {
		if (hc_entry->rmx_ssthresh == 0)
			hc_entry->rmx_ssthresh = hcml->rmx_ssthresh;
		else
			hc_entry->rmx_ssthresh =
			    (hc_entry->rmx_ssthresh + hcml->rmx_ssthresh) / 2;
		TCPSTAT_INC(tcps_cachedssthresh);
	}
	if (hcml->rmx_cwnd != 0) {
		if (hc_entry->rmx_cwnd == 0)
			hc_entry->rmx_cwnd = hcml->rmx_cwnd;
		else
			hc_entry->rmx_cwnd = ((uint64_t)hc_entry->rmx_cwnd +
			    (uint64_t)hcml->rmx_cwnd) / 2;
		/* TCPSTAT_INC(tcps_cachedcwnd); */
	}
	if (hcml->rmx_sendpipe != 0) {
		if (hc_entry->rmx_sendpipe == 0)
			hc_entry->rmx_sendpipe = hcml->rmx_sendpipe;
		else
			hc_entry->rmx_sendpipe =
			    ((uint64_t)hc_entry->rmx_sendpipe +
			    (uint64_t)hcml->rmx_sendpipe) /2;
		/* TCPSTAT_INC(tcps_cachedsendpipe); */
	}
	if (hcml->rmx_recvpipe != 0) {
		if (hc_entry->rmx_recvpipe == 0)
			hc_entry->rmx_recvpipe = hcml->rmx_recvpipe;
		else
			hc_entry->rmx_recvpipe =
			    ((uint64_t)hc_entry->rmx_recvpipe +
			    (uint64_t)hcml->rmx_recvpipe) /2;
		/* TCPSTAT_INC(tcps_cachedrecvpipe); */
	}

	TAILQ_REMOVE(&hc_entry->rmx_head->hch_bucket, hc_entry, rmx_q);
	TAILQ_INSERT_HEAD(&hc_entry->rmx_head->hch_bucket, hc_entry, rmx_q);
	THC_UNLOCK(&hc_entry->rmx_head->hch_mtx);
}