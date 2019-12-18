#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_short ;
typedef  int u_int32 ;
struct in_addr {int /*<<< orphan*/  member_0; } ;
struct TYPE_7__ {int addr; int mask; } ;
struct TYPE_8__ {TYPE_1__ v4; } ;
struct TYPE_9__ {scalar_t__ expire; int mflags; int /*<<< orphan*/  ippeerlimit; TYPE_2__ u; struct TYPE_9__* link; } ;
typedef  TYPE_3__ restrict_u ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (int,char*) ; 
 int /*<<< orphan*/  NTP_PORT ; 
 int RESM_NTPONLY ; 
 scalar_t__ current_time ; 
 int /*<<< orphan*/  free_res (TYPE_3__*,int const) ; 
 int /*<<< orphan*/  htonl (int) ; 
 int /*<<< orphan*/  inet_ntoa (struct in_addr) ; 
 TYPE_3__* restrictlist4 ; 

__attribute__((used)) static restrict_u *
match_restrict4_addr(
	u_int32	addr,
	u_short	port
	)
{
	const int	v6 = 0;
	restrict_u *	res;
	restrict_u *	next;

	for (res = restrictlist4; res != NULL; res = next) {
		struct in_addr	sia = { htonl(res->u.v4.addr) };

		next = res->link;
		DPRINTF(2, ("match_restrict4_addr: Checking %s, port %d ... ",
			    inet_ntoa(sia), port));
		if (   res->expire
		    && res->expire <= current_time)
			free_res(res, v6);	/* zeroes the contents */
		if (   res->u.v4.addr == (addr & res->u.v4.mask)
		    && (   !(RESM_NTPONLY & res->mflags)
			|| NTP_PORT == port)) {
			DPRINTF(2, ("MATCH: ippeerlimit %d\n", res->ippeerlimit));
			break;
		}
		DPRINTF(2, ("doesn't match: ippeerlimit %d\n", res->ippeerlimit));
	}
	return res;
}