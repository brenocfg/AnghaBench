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
typedef  int /*<<< orphan*/  bool_t ;
typedef  int /*<<< orphan*/  XDR ;
struct TYPE_3__ {int /*<<< orphan*/  r_owner; int /*<<< orphan*/  r_addr; int /*<<< orphan*/  r_netid; int /*<<< orphan*/  r_vers; int /*<<< orphan*/  r_prog; } ;
typedef  TYPE_1__ RPCB ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  RPC_MAXDATASIZE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  xdr_string (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xdr_uint32_t (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

bool_t
xdr_rpcb(XDR *xdrs, RPCB *objp)
{
	if (!xdr_uint32_t(xdrs, &objp->r_prog)) {
		return (FALSE);
	}
	if (!xdr_uint32_t(xdrs, &objp->r_vers)) {
		return (FALSE);
	}
	if (!xdr_string(xdrs, &objp->r_netid, RPC_MAXDATASIZE)) {
		return (FALSE);
	}
	if (!xdr_string(xdrs, &objp->r_addr, RPC_MAXDATASIZE)) {
		return (FALSE);
	}
	if (!xdr_string(xdrs, &objp->r_owner, RPC_MAXDATASIZE)) {
		return (FALSE);
	}
	return (TRUE);
}