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
struct llentry {long ln_ntick; int /*<<< orphan*/  lle_timer; scalar_t__ la_expire; } ;

/* Variables and functions */
 long INT_MAX ; 
 int /*<<< orphan*/  LLE_ADDREF (struct llentry*) ; 
 int /*<<< orphan*/  LLE_REMREF (struct llentry*) ; 
 int /*<<< orphan*/  LLE_WLOCK_ASSERT (struct llentry*) ; 
 int callout_reset (int /*<<< orphan*/ *,long,int /*<<< orphan*/ ,struct llentry*) ; 
 int callout_stop (int /*<<< orphan*/ *) ; 
 long hz ; 
 int /*<<< orphan*/  nd6_llinfo_timer ; 
 scalar_t__ time_uptime ; 

__attribute__((used)) static void
nd6_llinfo_settimer_locked(struct llentry *ln, long tick)
{
	int canceled;

	LLE_WLOCK_ASSERT(ln);

	if (tick < 0) {
		ln->la_expire = 0;
		ln->ln_ntick = 0;
		canceled = callout_stop(&ln->lle_timer);
	} else {
		ln->la_expire = time_uptime + tick / hz;
		LLE_ADDREF(ln);
		if (tick > INT_MAX) {
			ln->ln_ntick = tick - INT_MAX;
			canceled = callout_reset(&ln->lle_timer, INT_MAX,
			    nd6_llinfo_timer, ln);
		} else {
			ln->ln_ntick = 0;
			canceled = callout_reset(&ln->lle_timer, tick,
			    nd6_llinfo_timer, ln);
		}
	}
	if (canceled > 0)
		LLE_REMREF(ln);
}