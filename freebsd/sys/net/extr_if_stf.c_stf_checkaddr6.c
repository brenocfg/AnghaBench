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
struct stf_softc {int dummy; } ;
struct in_addr {int dummy; } ;
struct in6_addr {int dummy; } ;
struct ifnet {int dummy; } ;
typedef  int /*<<< orphan*/  in4 ;

/* Variables and functions */
 int /*<<< orphan*/  GET_V4 (struct in6_addr*) ; 
 scalar_t__ IN6_IS_ADDR_6TO4 (struct in6_addr*) ; 
 scalar_t__ IN6_IS_ADDR_V4COMPAT (struct in6_addr*) ; 
 scalar_t__ IN6_IS_ADDR_V4MAPPED (struct in6_addr*) ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ ,struct in_addr*,int) ; 
 int stf_checkaddr4 (struct stf_softc*,struct in_addr*,struct ifnet*) ; 

__attribute__((used)) static int
stf_checkaddr6(struct stf_softc *sc, struct in6_addr *in6, struct ifnet *inifp)
{
	/*
	 * check 6to4 addresses
	 */
	if (IN6_IS_ADDR_6TO4(in6)) {
		struct in_addr in4;
		bcopy(GET_V4(in6), &in4, sizeof(in4));
		return stf_checkaddr4(sc, &in4, inifp);
	}

	/*
	 * reject anything that look suspicious.  the test is implemented
	 * in ip6_input too, but we check here as well to
	 * (1) reject bad packets earlier, and
	 * (2) to be safe against future ip6_input change.
	 */
	if (IN6_IS_ADDR_V4COMPAT(in6) || IN6_IS_ADDR_V4MAPPED(in6))
		return -1;

	return 0;
}