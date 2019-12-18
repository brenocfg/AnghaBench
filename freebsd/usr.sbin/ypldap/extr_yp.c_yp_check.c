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
struct svc_req {int /*<<< orphan*/  rq_xprt; } ;
struct sockaddr_in {int dummy; } ;

/* Variables and functions */
 struct sockaddr_in* svc_getcaller (int /*<<< orphan*/ ) ; 

int
yp_check(struct svc_req *req)
{
	struct sockaddr_in	*caller;

	caller = svc_getcaller(req->rq_xprt);
	/*
	 * We might want to know who we allow here.
	 */
	return (0);
}