#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int i_len; int /*<<< orphan*/  ifr_name; void* ifr_data; int /*<<< orphan*/  i_name; void* i_data; int /*<<< orphan*/  i_type; } ;
struct TYPE_6__ {int /*<<< orphan*/  macaddr; } ;
struct TYPE_7__ {TYPE_1__ is_u; } ;
struct TYPE_8__ {TYPE_2__ info; } ;
struct wlanstatfoo_p {TYPE_5__ ifr; int /*<<< orphan*/  s; scalar_t__ mac; TYPE_5__ ireq; TYPE_3__ u_info; } ;
struct TYPE_9__ {int /*<<< orphan*/  macaddr; } ;
struct ieee80211req_sta_stats {TYPE_4__ is_u; } ;
struct ieee80211_stats {int dummy; } ;
struct ether_addr {int dummy; } ;
typedef  void* caddr_t ;

/* Variables and functions */
 int /*<<< orphan*/  IEEE80211_ADDR_COPY (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  IEEE80211_IOC_STA_INFO ; 
 int /*<<< orphan*/  IEEE80211_IOC_STA_STATS ; 
 int /*<<< orphan*/  SIOCG80211 ; 
 int /*<<< orphan*/  SIOCG80211STATS ; 
 int /*<<< orphan*/  err (int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ether_ntoa (struct ether_addr const*) ; 
 scalar_t__ ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_5__*) ; 
 int /*<<< orphan*/  warn (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
wlan_collect(struct wlanstatfoo_p *wf,
	struct ieee80211_stats *stats, struct ieee80211req_sta_stats *nstats)
{

	IEEE80211_ADDR_COPY(wf->u_info.info.is_u.macaddr, wf->mac);
	wf->ireq.i_type = IEEE80211_IOC_STA_INFO;
	wf->ireq.i_data = (caddr_t) &wf->u_info;
	wf->ireq.i_len = sizeof(wf->u_info);
	if (ioctl(wf->s, SIOCG80211, &wf->ireq) < 0) {
		warn("%s:%s (IEEE80211_IOC_STA_INFO)", wf->ireq.i_name,
		    ether_ntoa((const struct ether_addr*) wf->mac));
	}

	IEEE80211_ADDR_COPY(nstats->is_u.macaddr, wf->mac);
	wf->ireq.i_type = IEEE80211_IOC_STA_STATS;
	wf->ireq.i_data = (caddr_t) nstats;
	wf->ireq.i_len = sizeof(*nstats);
	if (ioctl(wf->s, SIOCG80211, &wf->ireq) < 0)
		warn("%s:%s (IEEE80211_IOC_STA_STATS)", wf->ireq.i_name,
		    ether_ntoa((const struct ether_addr*) wf->mac));

	wf->ifr.ifr_data = (caddr_t) stats;
	if (ioctl(wf->s, SIOCG80211STATS, &wf->ifr) < 0)
		err(1, "%s (SIOCG80211STATS)", wf->ifr.ifr_name);
}