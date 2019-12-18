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
struct ieee80211_txparams_req {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IEEE80211_IOC_TXPARAMS ; 
 int /*<<< orphan*/  set80211 (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct ieee80211_txparams_req*) ; 

__attribute__((used)) static void
settxparams_cb(int s, void *arg)
{
	struct ieee80211_txparams_req *txp = arg;
	set80211(s, IEEE80211_IOC_TXPARAMS, 0, sizeof(*txp), txp);
}