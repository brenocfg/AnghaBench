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
struct sockaddr_in6 {int dummy; } ;
struct sockaddr {int dummy; } ;
struct ifnet {int dummy; } ;

/* Variables and functions */
 int LLE_ADDRONLY ; 
 int nd6_resolve_slow (struct ifnet*,int,int /*<<< orphan*/ *,struct sockaddr_in6 const*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int
nd6_resolve_addr(struct ifnet *ifp, int flags, const struct sockaddr *dst,
    char *desten, uint32_t *pflags)
{
	int error;

	flags |= LLE_ADDRONLY;
	error = nd6_resolve_slow(ifp, flags, NULL,
	    (const struct sockaddr_in6 *)dst, desten, pflags, NULL);
	return (error);
}