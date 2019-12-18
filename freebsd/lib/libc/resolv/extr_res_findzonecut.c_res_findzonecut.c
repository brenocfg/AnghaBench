#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct in_addr {int dummy; } ;
struct TYPE_2__ {struct in_addr sin_addr; } ;
union res_sockaddr_union {TYPE_1__ sin; } ;
typedef  int /*<<< orphan*/  res_state ;
typedef  int /*<<< orphan*/  ns_class ;

/* Variables and functions */
 int RES_IPV4ONLY ; 
 int RES_IPV6ONLY ; 
 union res_sockaddr_union* calloc (int,int) ; 
 int /*<<< orphan*/  free (union res_sockaddr_union*) ; 
 int res_findzonecut2 (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int,char*,size_t,union res_sockaddr_union*,int) ; 

int
res_findzonecut(res_state statp, const char *dname, ns_class class, int opts,
		char *zname, size_t zsize, struct in_addr *addrs, int naddrs)
{
	int result, i;
	union res_sockaddr_union *u;

	
	opts |= RES_IPV4ONLY;
	opts &= ~RES_IPV6ONLY;

	u = calloc(naddrs, sizeof(*u));
	if (u == NULL)
		return(-1);

	result = res_findzonecut2(statp, dname, class, opts, zname, zsize,
				  u, naddrs);

	for (i = 0; i < result; i++) {
		addrs[i] = u[i].sin.sin_addr;
	}
	free(u);
	return (result);
}