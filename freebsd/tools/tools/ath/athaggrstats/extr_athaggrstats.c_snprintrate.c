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
 int IEEE80211_RATE_MCS ; 
 int /*<<< orphan*/  snprintf (char*,size_t,char*,int) ; 

__attribute__((used)) static void
snprintrate(char b[], size_t bs, int rate)
{
	if (rate & IEEE80211_RATE_MCS)
		snprintf(b, bs, "MCS%u", rate &~ IEEE80211_RATE_MCS);
	else if (rate & 1)
		snprintf(b, bs, "%u.5M", rate / 2);
	else
		snprintf(b, bs, "%uM", rate / 2);
}