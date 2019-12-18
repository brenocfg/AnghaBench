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
struct TYPE_3__ {int /*<<< orphan*/  rmtinfo; int /*<<< orphan*/  addrinfo; int /*<<< orphan*/  unsetinfo; int /*<<< orphan*/  setinfo; int /*<<< orphan*/  info; } ;
typedef  TYPE_1__ rpcb_stat ;
typedef  int /*<<< orphan*/  bool_t ;
typedef  int /*<<< orphan*/  XDR ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  xdr_int (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xdr_rpcbs_addrlist_ptr (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xdr_rpcbs_proc (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xdr_rpcbs_rmtcalllist_ptr (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

bool_t
xdr_rpcb_stat(XDR *xdrs, rpcb_stat *objp)
{

	if (!xdr_rpcbs_proc(xdrs, objp->info)) {
		return (FALSE);
	}
	if (!xdr_int(xdrs, &objp->setinfo)) {
		return (FALSE);
	}
	if (!xdr_int(xdrs, &objp->unsetinfo)) {
		return (FALSE);
	}
	if (!xdr_rpcbs_addrlist_ptr(xdrs, &objp->addrinfo)) {
		return (FALSE);
	}
	if (!xdr_rpcbs_rmtcalllist_ptr(xdrs, &objp->rmtinfo)) {
		return (FALSE);
	}
	return (TRUE);
}