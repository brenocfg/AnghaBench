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
typedef  scalar_t__ rpcb_stat_byvers ;
typedef  int /*<<< orphan*/  rpcb_stat ;
typedef  int /*<<< orphan*/  bool_t ;
typedef  int /*<<< orphan*/  XDR ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  RPCBVERS_STAT ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ xdr_rpcb_stat ; 
 int /*<<< orphan*/  xdr_vector (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

bool_t
xdr_rpcb_stat_byvers(XDR *xdrs, rpcb_stat_byvers objp)
{
	if (!xdr_vector(xdrs, (char *)(void *)objp, RPCBVERS_STAT,
	    sizeof (rpcb_stat), (xdrproc_t)xdr_rpcb_stat)) {
		return (FALSE);
	}
	return (TRUE);
}