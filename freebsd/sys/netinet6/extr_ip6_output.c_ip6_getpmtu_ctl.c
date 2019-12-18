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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  u_long ;
typedef  int /*<<< orphan*/  u_int ;
struct nhop6_extended {int /*<<< orphan*/  nh_mtu; struct ifnet* nh_ifp; } ;
struct in6_addr {int dummy; } ;
struct ifnet {int dummy; } ;

/* Variables and functions */
 int EHOSTUNREACH ; 
 int /*<<< orphan*/  NHR_REF ; 
 int /*<<< orphan*/  fib6_free_nh_ext (int /*<<< orphan*/ ,struct nhop6_extended*) ; 
 scalar_t__ fib6_lookup_nh_ext (int /*<<< orphan*/ ,struct in6_addr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct nhop6_extended*) ; 
 int /*<<< orphan*/  in6_splitscope (struct in6_addr const*,struct in6_addr*,int /*<<< orphan*/ *) ; 
 int ip6_calcmtu (struct ifnet*,struct in6_addr const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ip6_getpmtu_ctl(u_int fibnum, const struct in6_addr *dst, u_long *mtup)
{
	struct nhop6_extended nh6;
	struct in6_addr kdst;
	uint32_t scopeid;
	struct ifnet *ifp;
	u_long mtu;
	int error;

	in6_splitscope(dst, &kdst, &scopeid);
	if (fib6_lookup_nh_ext(fibnum, &kdst, scopeid, NHR_REF, 0, &nh6) != 0)
		return (EHOSTUNREACH);

	ifp = nh6.nh_ifp;
	mtu = nh6.nh_mtu;

	error = ip6_calcmtu(ifp, dst, mtu, mtup, NULL, 0);
	fib6_free_nh_ext(fibnum, &nh6);

	return (error);
}