#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct in_addr {int /*<<< orphan*/  member_0; } ;
struct TYPE_8__ {int /*<<< orphan*/  mask; int /*<<< orphan*/  addr; } ;
struct TYPE_7__ {struct in_addr mask; struct in_addr addr; } ;
struct TYPE_9__ {TYPE_2__ v4; TYPE_1__ v6; } ;
struct TYPE_10__ {int /*<<< orphan*/  link; int /*<<< orphan*/  expire; int /*<<< orphan*/  ippeerlimit; int /*<<< orphan*/  mflags; int /*<<< orphan*/  rflags; int /*<<< orphan*/  count; TYPE_3__ u; } ;
typedef  TYPE_4__ restrict_u ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  AF_INET6 ; 
 int INET6_ADDRSTRLEN ; 
 int /*<<< orphan*/  htonl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inet_ntop (int /*<<< orphan*/ ,struct in_addr*,char*,int) ; 
 int /*<<< orphan*/  mprintf (char*,TYPE_4__*,char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
dump_restrict(
	restrict_u *	res,
	int		is_ipv6
	)
{
	char as[INET6_ADDRSTRLEN];
	char ms[INET6_ADDRSTRLEN];

	if (is_ipv6) {
		inet_ntop(AF_INET6, &res->u.v6.addr, as, sizeof as);
		inet_ntop(AF_INET6, &res->u.v6.mask, ms, sizeof ms);
	} else {
		struct in_addr	sia = { htonl(res->u.v4.addr) };
		struct in_addr	sim = { htonl(res->u.v4.mask) };

		inet_ntop(AF_INET, &sia, as, sizeof as);
		inet_ntop(AF_INET, &sim, ms, sizeof ms);
	}
	mprintf("restrict node at %p: %s/%s count %d, rflags %05x, mflags %05x, ippeerlimit %d, expire %lu, next %p\n",
		res, as, ms, res->count, res->rflags, res->mflags,
		res->ippeerlimit, res->expire, res->link);
	return;
}