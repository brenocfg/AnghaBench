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
struct ieee80211_rx_ampdu {int rxa_flags; void* rxa_start; int /*<<< orphan*/  rxa_wnd; } ;
struct ieee80211_node {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IEEE80211_AGGR_BAWMAX ; 
 int IEEE80211_AGGR_RUNNING ; 
 int IEEE80211_AGGR_XCHGPEND ; 
 int /*<<< orphan*/  IEEE80211_BAPS_BUFSIZ ; 
 int /*<<< orphan*/  IEEE80211_BASEQ_START ; 
 void* MS (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ampdu_rx_purge (struct ieee80211_rx_ampdu*) ; 
 int /*<<< orphan*/  memset (struct ieee80211_rx_ampdu*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  min (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ampdu_rx_start(struct ieee80211_node *ni, struct ieee80211_rx_ampdu *rap,
	int baparamset, int batimeout, int baseqctl)
{
	int bufsiz = MS(baparamset, IEEE80211_BAPS_BUFSIZ);

	if (rap->rxa_flags & IEEE80211_AGGR_RUNNING) {
		/*
		 * AMPDU previously setup and not terminated with a DELBA,
		 * flush the reorder q's in case anything remains.
		 */
		ampdu_rx_purge(rap);
	}
	memset(rap, 0, sizeof(*rap));
	rap->rxa_wnd = (bufsiz == 0) ?
	    IEEE80211_AGGR_BAWMAX : min(bufsiz, IEEE80211_AGGR_BAWMAX);
	rap->rxa_start = MS(baseqctl, IEEE80211_BASEQ_START);
	rap->rxa_flags |=  IEEE80211_AGGR_RUNNING | IEEE80211_AGGR_XCHGPEND;

	return 0;
}