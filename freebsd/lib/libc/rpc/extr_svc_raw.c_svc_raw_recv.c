#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  x_op; } ;
struct svc_raw_private {TYPE_1__ xdr_stream; } ;
struct rpc_msg {int dummy; } ;
typedef  int /*<<< orphan*/  bool_t ;
typedef  TYPE_1__ XDR ;
typedef  int /*<<< orphan*/  SVCXPRT ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  XDR_DECODE ; 
 int /*<<< orphan*/  XDR_SETPOS (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct svc_raw_private* svc_raw_private ; 
 int /*<<< orphan*/  svcraw_lock ; 
 int /*<<< orphan*/  xdr_callmsg (TYPE_1__*,struct rpc_msg*) ; 

__attribute__((used)) static bool_t
svc_raw_recv(SVCXPRT *xprt, struct rpc_msg *msg)
{
	struct svc_raw_private *srp;
	XDR *xdrs;

	mutex_lock(&svcraw_lock);
	srp = svc_raw_private;
	if (srp == NULL) {
		mutex_unlock(&svcraw_lock);
		return (FALSE);
	}
	mutex_unlock(&svcraw_lock);

	xdrs = &srp->xdr_stream;
	xdrs->x_op = XDR_DECODE;
	(void) XDR_SETPOS(xdrs, 0);
	if (! xdr_callmsg(xdrs, msg)) {
		return (FALSE);
	}
	return (TRUE);
}