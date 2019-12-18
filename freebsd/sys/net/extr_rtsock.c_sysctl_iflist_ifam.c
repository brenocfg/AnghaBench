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
struct walkarg {scalar_t__ w_tmem; int /*<<< orphan*/  w_req; } ;
struct rt_addrinfo {int /*<<< orphan*/  rti_addrs; } ;
struct ifaddr {TYPE_1__* ifa_ifp; int /*<<< orphan*/  ifa_flags; } ;
struct ifa_msghdr {int /*<<< orphan*/  ifam_metric; scalar_t__ _ifam_spare1; int /*<<< orphan*/  ifam_index; int /*<<< orphan*/  ifam_flags; int /*<<< orphan*/  ifam_addrs; } ;
struct TYPE_2__ {int /*<<< orphan*/  if_metric; int /*<<< orphan*/  if_index; } ;

/* Variables and functions */
 int SYSCTL_OUT (int /*<<< orphan*/ ,scalar_t__,int) ; 

__attribute__((used)) static int
sysctl_iflist_ifam(struct ifaddr *ifa, struct rt_addrinfo *info,
    struct walkarg *w, int len)
{
	struct ifa_msghdr *ifam;

	ifam = (struct ifa_msghdr *)w->w_tmem;
	ifam->ifam_addrs = info->rti_addrs;
	ifam->ifam_flags = ifa->ifa_flags;
	ifam->ifam_index = ifa->ifa_ifp->if_index;
	ifam->_ifam_spare1 = 0;
	ifam->ifam_metric = ifa->ifa_ifp->if_metric;

	return (SYSCTL_OUT(w->w_req, w->w_tmem, len));
}