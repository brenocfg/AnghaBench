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
typedef  int /*<<< orphan*/  xdrproc_t ;
typedef  int /*<<< orphan*/  rpcbs_rmtcalllist_ptr ;
typedef  int /*<<< orphan*/  rpcbs_rmtcalllist ;
typedef  int /*<<< orphan*/  bool_t ;
typedef  int /*<<< orphan*/  XDR ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  xdr_pointer (int /*<<< orphan*/ *,char**,int,int /*<<< orphan*/ ) ; 
 scalar_t__ xdr_rpcbs_rmtcalllist ; 

bool_t
xdr_rpcbs_rmtcalllist_ptr(XDR *xdrs, rpcbs_rmtcalllist_ptr *objp)
{
	if (!xdr_pointer(xdrs, (char **)objp, sizeof (rpcbs_rmtcalllist),
			(xdrproc_t)xdr_rpcbs_rmtcalllist)) {
		return (FALSE);
	}
	return (TRUE);
}