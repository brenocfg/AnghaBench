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
 int IEEE80211_HTCAP_SHORTGI20 ; 
 int IEEE80211_HTCAP_SHORTGI40 ; 
 int /*<<< orphan*/  IEEE80211_IOC_SHORTGI ; 
 int /*<<< orphan*/  set80211 (int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
set80211shortgi(const char *val, int d, int s, const struct afswtch *rafp)
{
	set80211(s, IEEE80211_IOC_SHORTGI,
		d ? (IEEE80211_HTCAP_SHORTGI20 | IEEE80211_HTCAP_SHORTGI40) : 0,
		0, NULL);
}