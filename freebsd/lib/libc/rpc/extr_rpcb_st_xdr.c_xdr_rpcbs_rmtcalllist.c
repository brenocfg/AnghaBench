#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  xdrproc_t ;
struct rpcbs_rmtcalllist {int dummy; } ;
typedef  scalar_t__ rpcvers_t ;
typedef  scalar_t__ rpcprog_t ;
typedef  scalar_t__ rpcproc_t ;
struct TYPE_12__ {int success; int failure; int indirect; int /*<<< orphan*/  netid; scalar_t__ proc; scalar_t__ vers; scalar_t__ prog; struct rpcbs_rmtcalllist* next; } ;
typedef  TYPE_1__ rpcbs_rmtcalllist ;
typedef  int /*<<< orphan*/  int32_t ;
typedef  int /*<<< orphan*/  bool_t ;
struct TYPE_13__ {scalar_t__ x_op; } ;
typedef  TYPE_2__ XDR ;

/* Variables and functions */
 int BYTES_PER_XDR_UNIT ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ IXDR_GET_INT32 (int /*<<< orphan*/ *) ; 
 scalar_t__ IXDR_GET_U_INT32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IXDR_PUT_INT32 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  IXDR_PUT_U_INT32 (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  RPC_MAXDATASIZE ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ XDR_DECODE ; 
 scalar_t__ XDR_ENCODE ; 
 int /*<<< orphan*/ * XDR_INLINE (TYPE_2__*,int) ; 
 int /*<<< orphan*/  xdr_int (TYPE_2__*,int*) ; 
 int /*<<< orphan*/  xdr_pointer (TYPE_2__*,char**,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xdr_rpcproc (TYPE_2__*,scalar_t__*) ; 
 int /*<<< orphan*/  xdr_rpcprog (TYPE_2__*,scalar_t__*) ; 
 int /*<<< orphan*/  xdr_rpcvers (TYPE_2__*,scalar_t__*) ; 
 int /*<<< orphan*/  xdr_string (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

bool_t
xdr_rpcbs_rmtcalllist(XDR *xdrs, rpcbs_rmtcalllist *objp)
{
	int32_t *buf;
	struct rpcbs_rmtcalllist **pnext;

	if (xdrs->x_op == XDR_ENCODE) {
	buf = XDR_INLINE(xdrs, 6 * BYTES_PER_XDR_UNIT);
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
		if (!xdr_int(xdrs, &objp->success)) {
			return (FALSE);
		}
		if (!xdr_int(xdrs, &objp->failure)) {
			return (FALSE);
		}
		if (!xdr_int(xdrs, &objp->indirect)) {
			return (FALSE);
		}
	} else {
		IXDR_PUT_U_INT32(buf, objp->prog);
		IXDR_PUT_U_INT32(buf, objp->vers);
		IXDR_PUT_U_INT32(buf, objp->proc);
		IXDR_PUT_INT32(buf, objp->success);
		IXDR_PUT_INT32(buf, objp->failure);
		IXDR_PUT_INT32(buf, objp->indirect);
	}
	if (!xdr_string(xdrs, &objp->netid, RPC_MAXDATASIZE)) {
		return (FALSE);
	}
	pnext = &objp->next;
	if (!xdr_pointer(xdrs, (char **) pnext,
			sizeof (rpcbs_rmtcalllist),
			(xdrproc_t)xdr_rpcbs_rmtcalllist)) {
		return (FALSE);
	}
	return (TRUE);
	} else if (xdrs->x_op == XDR_DECODE) {
	buf = XDR_INLINE(xdrs, 6 * BYTES_PER_XDR_UNIT);
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
		if (!xdr_int(xdrs, &objp->success)) {
			return (FALSE);
		}
		if (!xdr_int(xdrs, &objp->failure)) {
			return (FALSE);
		}
		if (!xdr_int(xdrs, &objp->indirect)) {
			return (FALSE);
		}
	} else {
		objp->prog = (rpcprog_t)IXDR_GET_U_INT32(buf);
		objp->vers = (rpcvers_t)IXDR_GET_U_INT32(buf);
		objp->proc = (rpcproc_t)IXDR_GET_U_INT32(buf);
		objp->success = (int)IXDR_GET_INT32(buf);
		objp->failure = (int)IXDR_GET_INT32(buf);
		objp->indirect = (int)IXDR_GET_INT32(buf);
	}
	if (!xdr_string(xdrs, &objp->netid, RPC_MAXDATASIZE)) {
		return (FALSE);
	}
	if (!xdr_pointer(xdrs, (char **) pnext,
			sizeof (rpcbs_rmtcalllist),
			(xdrproc_t)xdr_rpcbs_rmtcalllist)) {
		return (FALSE);
	}
	return (TRUE);
	}
	if (!xdr_rpcprog(xdrs, &objp->prog)) {
		return (FALSE);
	}
	if (!xdr_rpcvers(xdrs, &objp->vers)) {
		return (FALSE);
	}
	if (!xdr_rpcproc(xdrs, &objp->proc)) {
		return (FALSE);
	}
	if (!xdr_int(xdrs, &objp->success)) {
		return (FALSE);
	}
	if (!xdr_int(xdrs, &objp->failure)) {
		return (FALSE);
	}
	if (!xdr_int(xdrs, &objp->indirect)) {
		return (FALSE);
	}
	if (!xdr_string(xdrs, &objp->netid, RPC_MAXDATASIZE)) {
		return (FALSE);
	}
	if (!xdr_pointer(xdrs, (char **) pnext,
			sizeof (rpcbs_rmtcalllist),
			(xdrproc_t)xdr_rpcbs_rmtcalllist)) {
		return (FALSE);
	}
	return (TRUE);
}