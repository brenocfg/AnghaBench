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
struct thread {int dummy; } ;
struct l_ifreq {int /*<<< orphan*/  ifr_flags; } ;
struct ifnet {int dummy; } ;
typedef  int /*<<< orphan*/  l_short ;
typedef  int /*<<< orphan*/  flags ;

/* Variables and functions */
 int copyout (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  linux_ifflags (struct ifnet*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
linux_gifflags(struct thread *td, struct ifnet *ifp, struct l_ifreq *ifr)
{
	l_short flags;

	linux_ifflags(ifp, &flags);

	return (copyout(&flags, &ifr->ifr_flags, sizeof(flags)));
}