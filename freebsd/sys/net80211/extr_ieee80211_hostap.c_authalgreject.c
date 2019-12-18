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
struct TYPE_2__ {int /*<<< orphan*/  is_rx_auth_unsupported; } ;
struct ieee80211vap {TYPE_1__ iv_stats; } ;
struct ieee80211_node {struct ieee80211vap* ni_vap; } ;
struct ieee80211_frame {int /*<<< orphan*/  i_addr2; } ;

/* Variables and functions */
 int /*<<< orphan*/  IEEE80211_DISCARD (struct ieee80211vap*,int /*<<< orphan*/ ,struct ieee80211_frame const*,int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  IEEE80211_FC0_SUBTYPE_AUTH ; 
 int /*<<< orphan*/  IEEE80211_MSG_ANY ; 
 int /*<<< orphan*/  ieee80211_send_error (struct ieee80211_node*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
authalgreject(struct ieee80211_node *ni, const struct ieee80211_frame *wh,
	int algo, int seq, int status)
{
	struct ieee80211vap *vap = ni->ni_vap;

	IEEE80211_DISCARD(vap, IEEE80211_MSG_ANY,
	    wh, NULL, "unsupported alg %d", algo);
	vap->iv_stats.is_rx_auth_unsupported++;
	ieee80211_send_error(ni, wh->i_addr2, IEEE80211_FC0_SUBTYPE_AUTH,
	    seq | (status << 16));
}