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
struct TYPE_3__ {int /*<<< orphan*/  sequence; int /*<<< orphan*/  stat; int /*<<< orphan*/  cookie; } ;
typedef  TYPE_1__ nlm4_shareres ;
typedef  int /*<<< orphan*/  bool_t ;
typedef  int /*<<< orphan*/  XDR ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  xdr_int (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xdr_netobj (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xdr_nlm4_stats (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

bool_t
xdr_nlm4_shareres(XDR *xdrs, nlm4_shareres *objp)
{

	if (!xdr_netobj(xdrs, &objp->cookie))
		return (FALSE);
	if (!xdr_nlm4_stats(xdrs, &objp->stat))
		return (FALSE);
	if (!xdr_int(xdrs, &objp->sequence))
		return (FALSE);
	return (TRUE);
}