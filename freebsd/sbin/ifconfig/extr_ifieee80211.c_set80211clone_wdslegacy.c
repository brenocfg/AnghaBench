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
struct afswtch {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  icp_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  IEEE80211_CLONE_WDSLEGACY ; 
 TYPE_1__ params ; 

__attribute__((used)) static void
set80211clone_wdslegacy(const char *val, int d, int s, const struct afswtch *rafp)
{
	if (d)
		params.icp_flags |= IEEE80211_CLONE_WDSLEGACY;
	else
		params.icp_flags &= ~IEEE80211_CLONE_WDSLEGACY;
}