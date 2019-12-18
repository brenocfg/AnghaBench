#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  i_len; int /*<<< orphan*/  i_data; int /*<<< orphan*/  i_type; } ;
struct wlanstatfoo_p {TYPE_1__ ireq; int /*<<< orphan*/  s; int /*<<< orphan*/  mac; } ;

/* Variables and functions */
 int /*<<< orphan*/  IEEE80211_ADDR_LEN ; 
 int /*<<< orphan*/  IEEE80211_IOC_BSSID ; 
 int /*<<< orphan*/  SIOCG80211 ; 
 int ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 

__attribute__((used)) static int
getbssid(struct wlanstatfoo_p *wf)
{
	wf->ireq.i_type = IEEE80211_IOC_BSSID;
	wf->ireq.i_data = wf->mac;
	wf->ireq.i_len = IEEE80211_ADDR_LEN;
	return ioctl(wf->s, SIOCG80211, &wf->ireq);
}