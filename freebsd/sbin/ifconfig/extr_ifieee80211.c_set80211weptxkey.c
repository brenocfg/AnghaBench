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
 int /*<<< orphan*/  IEEE80211_IOC_WEPTXKEY ; 
 scalar_t__ IEEE80211_KEYIX_NONE ; 
 scalar_t__ atoi (char const*) ; 
 scalar_t__ isundefarg (char const*) ; 
 int /*<<< orphan*/  set80211 (int,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
set80211weptxkey(const char *val, int d, int s, const struct afswtch *rafp)
{
	if (isundefarg(val))
		set80211(s, IEEE80211_IOC_WEPTXKEY, IEEE80211_KEYIX_NONE, 0, NULL);
	else
		set80211(s, IEEE80211_IOC_WEPTXKEY, atoi(val)-1, 0, NULL);
}