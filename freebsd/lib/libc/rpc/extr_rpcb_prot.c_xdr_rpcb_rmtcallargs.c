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
typedef  scalar_t__ u_long ;
typedef  scalar_t__ u_int ;
struct rpcb_rmtcallargs {int dummy; } ;
struct TYPE_2__ {scalar_t__ args_len; int /*<<< orphan*/  args_val; } ;
struct r_rpcb_rmtcallargs {TYPE_1__ args; int /*<<< orphan*/  (* xdr_args ) (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;int /*<<< orphan*/  proc; int /*<<< orphan*/  vers; int /*<<< orphan*/  prog; } ;
typedef  int /*<<< orphan*/  int32_t ;
typedef  int /*<<< orphan*/  bool_t ;
typedef  int /*<<< orphan*/  XDR ;

/* Variables and functions */
 int BYTES_PER_XDR_UNIT ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  IXDR_PUT_U_INT32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ XDR_GETPOS (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * XDR_INLINE (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  XDR_SETPOS (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xdr_rpcproc (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xdr_rpcprog (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xdr_rpcvers (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xdr_u_int (int /*<<< orphan*/ *,scalar_t__*) ; 

bool_t
xdr_rpcb_rmtcallargs(XDR *xdrs, struct rpcb_rmtcallargs *p)
{
	struct r_rpcb_rmtcallargs *objp =
	    (struct r_rpcb_rmtcallargs *)(void *)p;
	u_int lenposition, argposition, position;
	int32_t *buf;

	buf = XDR_INLINE(xdrs, 3 * BYTES_PER_XDR_UNIT);
	if (buf == NULL) {
		if (!xdr_rpcprog(xdrs, &objp->prog)) {
			return (FALSE);
		}
		if (!xdr_rpcvers(xdrs, &objp->vers)) {
			return (FALSE);
		}
		if (!xdr_rpcproc(xdrs, &objp->proc)) {
			return (FALSE);
		}
	} else {
		IXDR_PUT_U_INT32(buf, objp->prog);
		IXDR_PUT_U_INT32(buf, objp->vers);
		IXDR_PUT_U_INT32(buf, objp->proc);
	}

	/*
	 * All the jugglery for just getting the size of the arguments
	 */
	lenposition = XDR_GETPOS(xdrs);
	if (! xdr_u_int(xdrs, &(objp->args.args_len))) {
		return (FALSE);
	}
	argposition = XDR_GETPOS(xdrs);
	if (! (*objp->xdr_args)(xdrs, objp->args.args_val)) {
		return (FALSE);
	}
	position = XDR_GETPOS(xdrs);
	objp->args.args_len = (u_int)((u_long)position - (u_long)argposition);
	XDR_SETPOS(xdrs, lenposition);
	if (! xdr_u_int(xdrs, &(objp->args.args_len))) {
		return (FALSE);
	}
	XDR_SETPOS(xdrs, position);
	return (TRUE);
}