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
struct TYPE_2__ {int /*<<< orphan*/  ifa_ifp; } ;
struct in_ifaddr {int ia_garp_count; TYPE_1__ ia_ifa; int /*<<< orphan*/  ia_garp_timer; } ;
struct ifaddr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IF_ADDR_WLOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IF_ADDR_WUNLOCK (int /*<<< orphan*/ ) ; 
 scalar_t__ callout_reset (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,struct in_ifaddr*) ; 
 int /*<<< orphan*/  garp_rexmit ; 
 int hz ; 
 int /*<<< orphan*/  ifa_ref (struct ifaddr*) ; 

__attribute__((used)) static void
garp_timer_start(struct ifaddr *ifa)
{
	struct in_ifaddr *ia = (struct in_ifaddr *) ifa;

	IF_ADDR_WLOCK(ia->ia_ifa.ifa_ifp);
	ia->ia_garp_count = 0;
	if (callout_reset(&ia->ia_garp_timer, (1 << ia->ia_garp_count) * hz,
	    garp_rexmit, ia) == 0) {
		ifa_ref(ifa);
	}
	IF_ADDR_WUNLOCK(ia->ia_ifa.ifa_ifp);
}