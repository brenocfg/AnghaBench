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
struct mbuf {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  is_rx_badkeyid; } ;
struct ieee80211vap {TYPE_1__ iv_stats; } ;
struct ieee80211_key {struct ieee80211vap* wk_private; } ;

/* Variables and functions */

__attribute__((used)) static int
none_demic(struct ieee80211_key *k, struct mbuf *m, int force)
{
	struct ieee80211vap *vap = k->wk_private;

	vap->iv_stats.is_rx_badkeyid++;
	return 0;
}