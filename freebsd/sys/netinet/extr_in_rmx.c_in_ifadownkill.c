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
struct rtentry {scalar_t__ rt_ifa; int rt_flags; } ;
struct in_ifadown_arg {scalar_t__ ifa; scalar_t__ del; } ;

/* Variables and functions */
 int RTF_STATIC ; 

__attribute__((used)) static int
in_ifadownkill(const struct rtentry *rt, void *xap)
{
	struct in_ifadown_arg *ap = xap;

	if (rt->rt_ifa != ap->ifa)
		return (0);

	if ((rt->rt_flags & RTF_STATIC) != 0 && ap->del == 0)
		return (0);

	return (1);
}