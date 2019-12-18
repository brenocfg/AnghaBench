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
struct netconfig {int dummy; } ;
struct netbuf {int dummy; } ;
struct __rpc_sockinfo {int /*<<< orphan*/  si_af; } ;

/* Variables and functions */
 int /*<<< orphan*/  __rpc_nconf2sockinfo (struct netconfig const*,struct __rpc_sockinfo*) ; 
 char* __rpc_taddr2uaddr_af (int /*<<< orphan*/ ,struct netbuf const*) ; 

char *
taddr2uaddr(const struct netconfig *nconf, const struct netbuf *nbuf)
{
	struct __rpc_sockinfo si;

	if (!__rpc_nconf2sockinfo(nconf, &si))
		return NULL;
	return __rpc_taddr2uaddr_af(si.si_af, nbuf);
}