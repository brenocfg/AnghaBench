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
struct TYPE_4__ {scalar_t__ duplex; int /*<<< orphan*/  speed; scalar_t__ link_up; } ;
struct TYPE_3__ {TYPE_2__ s; } ;
struct octeon_link_info {TYPE_1__ link; } ;
struct lio {int /*<<< orphan*/  oct_dev; struct octeon_link_info linfo; } ;
struct ifnet {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIO_IFSTATE_REGISTERED ; 
 int /*<<< orphan*/  LIO_IFSTATE_RESETTING ; 
 struct lio* if_getsoftc (struct ifnet*) ; 
 int /*<<< orphan*/  lio_dev_info (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ lio_ifstate_check (struct lio*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
print_link_info(struct ifnet *ifp)
{
	struct lio	*lio = if_getsoftc(ifp);

	if (!lio_ifstate_check(lio, LIO_IFSTATE_RESETTING) &&
	    lio_ifstate_check(lio, LIO_IFSTATE_REGISTERED)) {
		struct octeon_link_info *linfo = &lio->linfo;

		if (linfo->link.s.link_up) {
			lio_dev_info(lio->oct_dev, "%d Mbps %s Duplex UP\n",
				     linfo->link.s.speed,
				     (linfo->link.s.duplex) ? "Full" : "Half");
		} else {
			lio_dev_info(lio->oct_dev, "Link Down\n");
		}
	}
}