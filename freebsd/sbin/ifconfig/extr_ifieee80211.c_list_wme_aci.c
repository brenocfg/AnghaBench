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

/* Variables and functions */
 int /*<<< orphan*/  IEEE80211_IOC_WME_ACKPOLICY ; 
 int /*<<< orphan*/  IEEE80211_IOC_WME_ACM ; 
 int /*<<< orphan*/  IEEE80211_IOC_WME_AIFS ; 
 int /*<<< orphan*/  IEEE80211_IOC_WME_CWMAX ; 
 int /*<<< orphan*/  IEEE80211_IOC_WME_CWMIN ; 
 int /*<<< orphan*/  IEEE80211_IOC_WME_TXOPLIMIT ; 
 int IEEE80211_WMEPARAM_BSS ; 
 int get80211wme (int,int /*<<< orphan*/ ,int,int*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 scalar_t__ verbose ; 

__attribute__((used)) static void
list_wme_aci(int s, const char *tag, int ac)
{
	int val;

	printf("\t%s", tag);

	/* show WME BSS parameters */
	if (get80211wme(s, IEEE80211_IOC_WME_CWMIN, ac, &val) != -1)
		printf(" cwmin %2u", val);
	if (get80211wme(s, IEEE80211_IOC_WME_CWMAX, ac, &val) != -1)
		printf(" cwmax %2u", val);
	if (get80211wme(s, IEEE80211_IOC_WME_AIFS, ac, &val) != -1)
		printf(" aifs %2u", val);
	if (get80211wme(s, IEEE80211_IOC_WME_TXOPLIMIT, ac, &val) != -1)
		printf(" txopLimit %3u", val);
	if (get80211wme(s, IEEE80211_IOC_WME_ACM, ac, &val) != -1) {
		if (val)
			printf(" acm");
		else if (verbose)
			printf(" -acm");
	}
	/* !BSS only */
	if ((ac & IEEE80211_WMEPARAM_BSS) == 0) {
		if (get80211wme(s, IEEE80211_IOC_WME_ACKPOLICY, ac, &val) != -1) {
			if (!val)
				printf(" -ack");
			else if (verbose)
				printf(" ack");
		}
	}
	printf("\n");
}