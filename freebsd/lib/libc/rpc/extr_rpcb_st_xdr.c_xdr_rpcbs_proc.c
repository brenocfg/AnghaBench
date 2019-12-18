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
typedef  scalar_t__ rpcbs_proc ;
typedef  int /*<<< orphan*/  bool_t ;
typedef  int /*<<< orphan*/  XDR ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  RPCBSTAT_HIGHPROC ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ xdr_int ; 
 int /*<<< orphan*/  xdr_vector (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

bool_t
xdr_rpcbs_proc(XDR *xdrs, rpcbs_proc objp)
{
	if (!xdr_vector(xdrs, (char *)(void *)objp, RPCBSTAT_HIGHPROC,
	    sizeof (int), (xdrproc_t)xdr_int)) {
		return (FALSE);
	}
	return (TRUE);
}