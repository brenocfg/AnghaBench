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
struct ieee80211com {int /*<<< orphan*/  (* ic_update_promisc ) (struct ieee80211com*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct ieee80211com*) ; 

__attribute__((used)) static void
update_promisc(void *arg, int npending)
{
	struct ieee80211com *ic = arg;

	ic->ic_update_promisc(ic);
}