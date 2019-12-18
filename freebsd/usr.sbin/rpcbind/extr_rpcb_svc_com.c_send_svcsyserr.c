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
struct finfo {scalar_t__ reply_type; } ;
typedef  int /*<<< orphan*/  SVCXPRT ;

/* Variables and functions */
 scalar_t__ RPCBPROC_INDIRECT ; 
 int /*<<< orphan*/  svcerr_systemerr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xprt_set_caller (int /*<<< orphan*/ *,struct finfo*) ; 

__attribute__((used)) static void
send_svcsyserr(SVCXPRT *xprt, struct finfo *fi)
{
	if (fi->reply_type == RPCBPROC_INDIRECT) {
		xprt_set_caller(xprt, fi);
		svcerr_systemerr(xprt);
	}
	return;
}