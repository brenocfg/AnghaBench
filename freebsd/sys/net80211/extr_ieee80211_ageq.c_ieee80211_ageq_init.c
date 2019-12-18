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
struct ieee80211_ageq {int aq_maxlen; } ;

/* Variables and functions */
 int /*<<< orphan*/  IEEE80211_AGEQ_INIT (struct ieee80211_ageq*,char const*) ; 
 int /*<<< orphan*/  memset (struct ieee80211_ageq*,int /*<<< orphan*/ ,int) ; 

void
ieee80211_ageq_init(struct ieee80211_ageq *aq, int maxlen, const char *name)
{
	memset(aq, 0, sizeof(*aq));
	aq->aq_maxlen = maxlen;
	IEEE80211_AGEQ_INIT(aq, name);		/* OS-dependent setup */
}