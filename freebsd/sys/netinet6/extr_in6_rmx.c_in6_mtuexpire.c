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
struct rtentry {int rt_flags; int /*<<< orphan*/  rt_expire; } ;
struct mtuex_arg {int /*<<< orphan*/  nextstop; } ;

/* Variables and functions */
 int RTF_PROBEMTU ; 
 int /*<<< orphan*/  lmin (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  time_uptime ; 

__attribute__((used)) static int
in6_mtuexpire(struct rtentry *rt, void *rock)
{
	struct mtuex_arg *ap = rock;

	if (rt->rt_expire && !(rt->rt_flags & RTF_PROBEMTU)) {
		if (rt->rt_expire <= time_uptime) {
			rt->rt_flags |= RTF_PROBEMTU;
		} else {
			ap->nextstop = lmin(ap->nextstop, rt->rt_expire);
		}
	}

	return (0);
}