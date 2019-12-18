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
struct cf_conn {scalar_t__ strm_stat; int /*<<< orphan*/  xdrs; } ;
typedef  enum xprt_stat { ____Placeholder_xprt_stat } xprt_stat ;
struct TYPE_3__ {scalar_t__ xp_p1; } ;
typedef  TYPE_1__ SVCXPRT ;

/* Variables and functions */
 scalar_t__ XPRT_DIED ; 
 int XPRT_IDLE ; 
 int XPRT_MOREREQS ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xdrrec_eof (int /*<<< orphan*/ *) ; 

__attribute__((used)) static enum xprt_stat
svc_vc_stat(SVCXPRT *xprt)
{
	struct cf_conn *cd;

	assert(xprt != NULL);

	cd = (struct cf_conn *)(xprt->xp_p1);

	if (cd->strm_stat == XPRT_DIED)
		return (XPRT_DIED);
	if (! xdrrec_eof(&(cd->xdrs)))
		return (XPRT_MOREREQS);
	return (XPRT_IDLE);
}