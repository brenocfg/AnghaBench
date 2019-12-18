#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u_int ;
struct recvbuf {int dummy; } ;
struct TYPE_4__ {scalar_t__ ifnum; struct TYPE_4__* elink; } ;
typedef  TYPE_1__ endpt ;

/* Variables and functions */
 int /*<<< orphan*/  ctl_flushpkt (int /*<<< orphan*/ ) ; 
 TYPE_1__* ep_list ; 
 int /*<<< orphan*/  send_ifstats_entry (TYPE_1__*,scalar_t__) ; 
 scalar_t__ sys_ifnum ; 

__attribute__((used)) static void
read_ifstats(
	struct recvbuf *	rbufp
	)
{
	u_int	ifidx;
	endpt *	la;

	/*
	 * loop over [0..sys_ifnum] searching ep_list for each
	 * ifnum in turn.
	 */
	for (ifidx = 0; ifidx < sys_ifnum; ifidx++) {
		for (la = ep_list; la != NULL; la = la->elink)
			if (ifidx == la->ifnum)
				break;
		if (NULL == la)
			continue;
		/* return stats for one local address */
		send_ifstats_entry(la, ifidx);
	}
	ctl_flushpkt(0);
}