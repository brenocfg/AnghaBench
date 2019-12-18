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
typedef  int /*<<< orphan*/  uint32_t ;
struct in_conninfo {int dummy; } ;
struct hc_metrics {TYPE_1__* rmx_head; int /*<<< orphan*/  rmx_mtu; int /*<<< orphan*/  rmx_expire; int /*<<< orphan*/  rmx_hits; } ;
struct TYPE_4__ {int /*<<< orphan*/  expire; } ;
struct TYPE_3__ {int /*<<< orphan*/  hch_mtx; } ;

/* Variables and functions */
 int /*<<< orphan*/  THC_UNLOCK (int /*<<< orphan*/ *) ; 
 TYPE_2__ V_tcp_hostcache ; 
 int /*<<< orphan*/  V_tcp_use_hostcache ; 
 struct hc_metrics* tcp_hc_lookup (struct in_conninfo*) ; 

uint32_t
tcp_hc_getmtu(struct in_conninfo *inc)
{
	struct hc_metrics *hc_entry;
	uint32_t mtu;

	if (!V_tcp_use_hostcache)
		return 0;

	hc_entry = tcp_hc_lookup(inc);
	if (hc_entry == NULL) {
		return 0;
	}
	hc_entry->rmx_hits++;
	hc_entry->rmx_expire = V_tcp_hostcache.expire; /* start over again */

	mtu = hc_entry->rmx_mtu;
	THC_UNLOCK(&hc_entry->rmx_head->hch_mtx);
	return mtu;
}