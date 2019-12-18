#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct rt_msghdr {scalar_t__ rtm_type; scalar_t__ rtm_version; } ;
struct if_announcemsghdr {scalar_t__ ifan_what; } ;
struct ieee80211req {int sr_flags; int i_len; struct ieee80211req* i_data; scalar_t__ sr_nssid; int /*<<< orphan*/  sr_duration; int /*<<< orphan*/  i_type; int /*<<< orphan*/  i_name; } ;
struct ieee80211_scan_req {int sr_flags; int i_len; struct ieee80211_scan_req* i_data; scalar_t__ sr_nssid; int /*<<< orphan*/  sr_duration; int /*<<< orphan*/  i_type; int /*<<< orphan*/  i_name; } ;
typedef  int /*<<< orphan*/  sr ;
typedef  int /*<<< orphan*/  ireq ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int IEEE80211_IOC_SCAN_ACTIVE ; 
 int IEEE80211_IOC_SCAN_BGSCAN ; 
 int /*<<< orphan*/  IEEE80211_IOC_SCAN_FOREVER ; 
 int IEEE80211_IOC_SCAN_NOPICK ; 
 int IEEE80211_IOC_SCAN_ONCE ; 
 int /*<<< orphan*/  IEEE80211_IOC_SCAN_REQ ; 
 int /*<<< orphan*/  PF_ROUTE ; 
 scalar_t__ RTM_IEEE80211 ; 
 scalar_t__ RTM_IEEE80211_SCAN ; 
 scalar_t__ RTM_VERSION ; 
 int /*<<< orphan*/  SIOCS80211 ; 
 int /*<<< orphan*/  SOCK_RAW ; 
 int /*<<< orphan*/  close (int) ; 
 scalar_t__ ioctl (int,int /*<<< orphan*/ ,struct ieee80211req*) ; 
 int /*<<< orphan*/  memset (struct ieee80211req*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  name ; 
 int /*<<< orphan*/  perror (char*) ; 
 scalar_t__ read (int,char*,int) ; 
 int socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
scan_and_wait(int s)
{
	struct ieee80211_scan_req sr;
	struct ieee80211req ireq;
	int sroute;

	sroute = socket(PF_ROUTE, SOCK_RAW, 0);
	if (sroute < 0) {
		perror("socket(PF_ROUTE,SOCK_RAW)");
		return;
	}
	(void) memset(&ireq, 0, sizeof(ireq));
	(void) strlcpy(ireq.i_name, name, sizeof(ireq.i_name));
	ireq.i_type = IEEE80211_IOC_SCAN_REQ;

	memset(&sr, 0, sizeof(sr));
	sr.sr_flags = IEEE80211_IOC_SCAN_ACTIVE
		    | IEEE80211_IOC_SCAN_BGSCAN
		    | IEEE80211_IOC_SCAN_NOPICK
		    | IEEE80211_IOC_SCAN_ONCE;
	sr.sr_duration = IEEE80211_IOC_SCAN_FOREVER;
	sr.sr_nssid = 0;

	ireq.i_data = &sr;
	ireq.i_len = sizeof(sr);
	/*
	 * NB: only root can trigger a scan so ignore errors. Also ignore
	 * possible errors from net80211, even if no new scan could be
	 * started there might still be a valid scan cache.
	 */
	if (ioctl(s, SIOCS80211, &ireq) == 0) {
		char buf[2048];
		struct if_announcemsghdr *ifan;
		struct rt_msghdr *rtm;

		do {
			if (read(sroute, buf, sizeof(buf)) < 0) {
				perror("read(PF_ROUTE)");
				break;
			}
			rtm = (struct rt_msghdr *) buf;
			if (rtm->rtm_version != RTM_VERSION)
				break;
			ifan = (struct if_announcemsghdr *) rtm;
		} while (rtm->rtm_type != RTM_IEEE80211 ||
		    ifan->ifan_what != RTM_IEEE80211_SCAN);
	}
	close(sroute);
}