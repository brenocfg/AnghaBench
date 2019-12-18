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
struct ieee80211_channel {int dummy; } ;
struct ath_softc {int dummy; } ;

/* Variables and functions */

int
ath_dfs_tasklet_needed(struct ath_softc *sc, struct ieee80211_channel *chan)
{
	return (0);
}