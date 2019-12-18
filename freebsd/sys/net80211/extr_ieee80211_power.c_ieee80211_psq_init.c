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
struct ieee80211_psq {int /*<<< orphan*/  psq_maxlen; } ;

/* Variables and functions */
 int /*<<< orphan*/  IEEE80211_PSQ_INIT (struct ieee80211_psq*,char const*) ; 
 int /*<<< orphan*/  IEEE80211_PS_MAX_QUEUE ; 
 int /*<<< orphan*/  memset (struct ieee80211_psq*,int /*<<< orphan*/ ,int) ; 

void
ieee80211_psq_init(struct ieee80211_psq *psq, const char *name)
{
	memset(psq, 0, sizeof(*psq));
	psq->psq_maxlen = IEEE80211_PS_MAX_QUEUE;
	IEEE80211_PSQ_INIT(psq, name);		/* OS-dependent setup */
}