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
struct in_conninfo {int dummy; } ;
struct hc_metrics_lite {int /*<<< orphan*/  rmx_recvpipe; int /*<<< orphan*/  rmx_sendpipe; int /*<<< orphan*/  rmx_cwnd; int /*<<< orphan*/  rmx_rttvar; int /*<<< orphan*/  rmx_rtt; int /*<<< orphan*/  rmx_ssthresh; int /*<<< orphan*/  rmx_mtu; } ;
struct hc_metrics {TYPE_1__* rmx_head; int /*<<< orphan*/  rmx_recvpipe; int /*<<< orphan*/  rmx_sendpipe; int /*<<< orphan*/  rmx_cwnd; int /*<<< orphan*/  rmx_rttvar; int /*<<< orphan*/  rmx_rtt; int /*<<< orphan*/  rmx_ssthresh; int /*<<< orphan*/  rmx_mtu; int /*<<< orphan*/  rmx_expire; int /*<<< orphan*/  rmx_hits; } ;
struct TYPE_4__ {int /*<<< orphan*/  expire; } ;
struct TYPE_3__ {int /*<<< orphan*/  hch_mtx; } ;

/* Variables and functions */
 int /*<<< orphan*/  THC_UNLOCK (int /*<<< orphan*/ *) ; 
 TYPE_2__ V_tcp_hostcache ; 
 int /*<<< orphan*/  V_tcp_use_hostcache ; 
 int /*<<< orphan*/  bzero (struct hc_metrics_lite*,int) ; 
 struct hc_metrics* tcp_hc_lookup (struct in_conninfo*) ; 

void
tcp_hc_get(struct in_conninfo *inc, struct hc_metrics_lite *hc_metrics_lite)
{
	struct hc_metrics *hc_entry;

	if (!V_tcp_use_hostcache)
		return;

	/*
	 * Find the right bucket.
	 */
	hc_entry = tcp_hc_lookup(inc);

	/*
	 * If we don't have an existing object.
	 */
	if (hc_entry == NULL) {
		bzero(hc_metrics_lite, sizeof(*hc_metrics_lite));
		return;
	}
	hc_entry->rmx_hits++;
	hc_entry->rmx_expire = V_tcp_hostcache.expire; /* start over again */

	hc_metrics_lite->rmx_mtu = hc_entry->rmx_mtu;
	hc_metrics_lite->rmx_ssthresh = hc_entry->rmx_ssthresh;
	hc_metrics_lite->rmx_rtt = hc_entry->rmx_rtt;
	hc_metrics_lite->rmx_rttvar = hc_entry->rmx_rttvar;
	hc_metrics_lite->rmx_cwnd = hc_entry->rmx_cwnd;
	hc_metrics_lite->rmx_sendpipe = hc_entry->rmx_sendpipe;
	hc_metrics_lite->rmx_recvpipe = hc_entry->rmx_recvpipe;

	/*
	 * Unlock bucket row.
	 */
	THC_UNLOCK(&hc_entry->rmx_head->hch_mtx);
}