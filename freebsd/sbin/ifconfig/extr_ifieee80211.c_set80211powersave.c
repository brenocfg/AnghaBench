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
struct afswtch {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IEEE80211_IOC_POWERSAVE ; 
 int /*<<< orphan*/  IEEE80211_POWERSAVE_OFF ; 
 int /*<<< orphan*/  IEEE80211_POWERSAVE_ON ; 
 int /*<<< orphan*/  set80211 (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
set80211powersave(const char *val, int d, int s, const struct afswtch *rafp)
{
	if (d == 0)
		set80211(s, IEEE80211_IOC_POWERSAVE, IEEE80211_POWERSAVE_OFF,
		    0, NULL);
	else
		set80211(s, IEEE80211_IOC_POWERSAVE, IEEE80211_POWERSAVE_ON,
		    0, NULL);
}