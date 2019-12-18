#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  union res_sockaddr_union {int dummy; } res_sockaddr_union ;
typedef  int /*<<< orphan*/  rrset_ns ;
struct TYPE_7__ {int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ rr_ns ;
typedef  int /*<<< orphan*/  res_state ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (char*) ; 
 TYPE_1__* HEAD (int /*<<< orphan*/ ) ; 
 TYPE_1__* NEXT (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int add_addrs (int /*<<< orphan*/ ,TYPE_1__*,union res_sockaddr_union*,int) ; 
 TYPE_1__* find_ns (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  link ; 
 int ns_samename (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static int
satisfy(res_state statp, const char *mname, rrset_ns *nsrrsp,
	union res_sockaddr_union *addrs, int naddrs)
{
	rr_ns *nsrr;
	int n, x;

	n = 0;
	nsrr = find_ns(nsrrsp, mname);
	if (nsrr != NULL) {
		x = add_addrs(statp, nsrr, addrs, naddrs);
		addrs += x;
		naddrs -= x;
		n += x;
	}
	for (nsrr = HEAD(*nsrrsp);
	     nsrr != NULL && naddrs > 0;
	     nsrr = NEXT(nsrr, link))
		if (ns_samename(nsrr->name, mname) != 1) {
			x = add_addrs(statp, nsrr, addrs, naddrs);
			addrs += x;
			naddrs -= x;
			n += x;
		}
	DPRINTF(("satisfy(%s): %d", mname, n));
	return (n);
}