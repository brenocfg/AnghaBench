#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct socket {int dummy; } ;
struct netconfig {int dummy; } ;
struct __rpc_sockinfo {int /*<<< orphan*/  si_proto; int /*<<< orphan*/  si_socktype; int /*<<< orphan*/  si_af; } ;
struct TYPE_3__ {int /*<<< orphan*/  td_ucred; } ;

/* Variables and functions */
 int /*<<< orphan*/  __rpc_nconf2sockinfo (struct netconfig const*,struct __rpc_sockinfo*) ; 
 TYPE_1__* curthread ; 
 int socreate (int /*<<< orphan*/ ,struct socket**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 

struct socket *
__rpc_nconf2socket(const struct netconfig *nconf)
{
	struct __rpc_sockinfo si;
	struct socket *so;
	int error;

	if (!__rpc_nconf2sockinfo(nconf, &si))
		return 0;

	so = NULL;
	error =  socreate(si.si_af, &so, si.si_socktype, si.si_proto,
	    curthread->td_ucred, curthread);

	if (error)
		return NULL;
	else
		return so;
}