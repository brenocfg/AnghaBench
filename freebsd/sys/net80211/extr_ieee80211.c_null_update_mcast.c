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
struct ieee80211com {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ic_printf (struct ieee80211com*,char*) ; 

__attribute__((used)) static void
null_update_mcast(struct ieee80211com *ic)
{

	ic_printf(ic, "need multicast update callback\n");
}