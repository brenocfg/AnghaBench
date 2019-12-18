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
struct __rpc_sockinfo {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __rpc_fd2sockinfo (int,struct __rpc_sockinfo*) ; 
 int /*<<< orphan*/  __rpc_sockinfo2netid (struct __rpc_sockinfo*,char const**) ; 
 struct netconfig* getnetconfigent (char*) ; 

struct netconfig *
__rpcgettp(int fd)
{
	const char *netid;
	struct __rpc_sockinfo si;

	if (!__rpc_fd2sockinfo(fd, &si))
		return NULL;

	if (!__rpc_sockinfo2netid(&si, &netid))
		return NULL;

	/*LINTED const castaway*/
	return getnetconfigent((char *)netid);
}