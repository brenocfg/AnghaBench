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
struct ieee80211_alq_rec {int dummy; } ;
struct ale {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALQ_NOWAIT ; 
 struct ale* alq_getn (int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_alq ; 
 int /*<<< orphan*/  ieee80211_alq_logged ; 
 int /*<<< orphan*/  ieee80211_alq_lost ; 

__attribute__((used)) static struct ale *
ieee80211_alq_get(size_t len)
{
	struct ale *ale;

	ale = alq_getn(ieee80211_alq, len + sizeof(struct ieee80211_alq_rec),
	    ALQ_NOWAIT);
	if (!ale)
		ieee80211_alq_lost++;
	else
		ieee80211_alq_logged++;
	return ale;
}