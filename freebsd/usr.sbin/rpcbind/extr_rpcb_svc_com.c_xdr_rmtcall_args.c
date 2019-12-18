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
struct r_rmtcall_args {int /*<<< orphan*/  rmt_args; int /*<<< orphan*/  rmt_proc; int /*<<< orphan*/  rmt_vers; int /*<<< orphan*/  rmt_prog; } ;
typedef  int /*<<< orphan*/  bool_t ;
typedef  int /*<<< orphan*/  XDR ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  xdr_encap_parms (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ xdr_rpcproc (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ xdr_rpcprog (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ xdr_rpcvers (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool_t
xdr_rmtcall_args(XDR *xdrs, struct r_rmtcall_args *cap)
{
	/* does not get the address or the arguments */
	if (xdr_rpcprog(xdrs, &(cap->rmt_prog)) &&
	    xdr_rpcvers(xdrs, &(cap->rmt_vers)) &&
	    xdr_rpcproc(xdrs, &(cap->rmt_proc))) {
		return (xdr_encap_parms(xdrs, &(cap->rmt_args)));
	}
	return (FALSE);
}