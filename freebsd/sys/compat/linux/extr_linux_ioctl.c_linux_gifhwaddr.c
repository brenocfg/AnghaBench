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
struct l_sockaddr {int dummy; } ;
struct l_ifreq {int /*<<< orphan*/  ifr_hwaddr; } ;
struct ifnet {int dummy; } ;
typedef  int /*<<< orphan*/  lsa ;

/* Variables and functions */
 int ENOENT ; 
 int copyout (struct l_sockaddr*,int /*<<< orphan*/ *,int) ; 
 scalar_t__ linux_ifhwaddr (struct ifnet*,struct l_sockaddr*) ; 

__attribute__((used)) static int
linux_gifhwaddr(struct ifnet *ifp, struct l_ifreq *ifr)
{
	struct l_sockaddr lsa;

	if (linux_ifhwaddr(ifp, &lsa) != 0)
		return (ENOENT);

	return (copyout(&lsa, &ifr->ifr_hwaddr, sizeof(lsa)));
}