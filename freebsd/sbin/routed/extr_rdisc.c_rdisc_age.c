#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ time_t ;
struct dr {scalar_t__ dr_ts; scalar_t__ dr_gate; scalar_t__ dr_life; TYPE_1__* dr_ifp; } ;
typedef  scalar_t__ naddr ;
struct TYPE_4__ {scalar_t__ tv_sec; } ;
struct TYPE_3__ {int /*<<< orphan*/  int_name; } ;

/* Variables and functions */
 size_t MAX_ADS ; 
 scalar_t__ SUPPLY_INTERVAL ; 
 int /*<<< orphan*/  age (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * cur_drp ; 
 struct dr* drs ; 
 int /*<<< orphan*/  naddr_ntoa (scalar_t__) ; 
 TYPE_2__ now ; 
 int /*<<< orphan*/  rdisc_adv () ; 
 int /*<<< orphan*/  rdisc_sol () ; 
 int /*<<< orphan*/  rdisc_sort () ; 
 scalar_t__ rip_sock ; 
 scalar_t__ supplier ; 
 int /*<<< orphan*/  trace_act (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
rdisc_age(naddr bad_gate)
{
	time_t sec;
	struct dr *drp;


	/* If only advertising, then do only that. */
	if (supplier) {
		/* If switching from client to server, get rid of old
		 * default routes.
		 */
		if (cur_drp != NULL)
			rdisc_sort();
		rdisc_adv();
		return;
	}

	/* If we are being told about a bad router,
	 * then age the discovered default route, and if there is
	 * no alternative, solicit a replacement.
	 */
	if (bad_gate != 0) {
		/* Look for the bad discovered default route.
		 * Age it and note its interface.
		 */
		for (drp = drs; drp < &drs[MAX_ADS]; drp++) {
			if (drp->dr_ts == 0)
				continue;

			/* When we find the bad router, then age the route
			 * to at most SUPPLY_INTERVAL.
			 * This is contrary to RFC 1256, but defends against
			 * black holes.
			 */
			if (drp->dr_gate == bad_gate) {
				sec = (now.tv_sec - drp->dr_life
				       + SUPPLY_INTERVAL);
				if (drp->dr_ts > sec) {
					trace_act("age 0.0.0.0 --> %s via %s",
						  naddr_ntoa(drp->dr_gate),
						  drp->dr_ifp->int_name);
					drp->dr_ts = sec;
				}
				break;
			}
		}
	}

	rdisc_sol();
	rdisc_sort();

	/* Delete old redirected routes to keep the kernel table small,
	 * and to prevent black holes.  Check that the kernel table
	 * matches the daemon table (i.e. has the default route).
	 * But only if RIP is not running and we are not dealing with
	 * a bad gateway, since otherwise age() will be called.
	 */
	if (rip_sock < 0 && bad_gate == 0)
		age(0);
}