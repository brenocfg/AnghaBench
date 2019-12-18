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
struct TYPE_3__ {int /*<<< orphan*/  l_len; int /*<<< orphan*/  l_offset; int /*<<< orphan*/  svid; int /*<<< orphan*/  oh; int /*<<< orphan*/  fh; int /*<<< orphan*/  caller_name; } ;
typedef  TYPE_1__ nlm_lock ;
typedef  int /*<<< orphan*/  bool_t ;
typedef  int /*<<< orphan*/  XDR ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  LM_MAXSTRLEN ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  xdr_int (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xdr_netobj (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xdr_string (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xdr_u_int (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

bool_t
xdr_nlm_lock(XDR *xdrs, nlm_lock *objp)
{

	if (!xdr_string(xdrs, &objp->caller_name, LM_MAXSTRLEN))
		return (FALSE);
	if (!xdr_netobj(xdrs, &objp->fh))
		return (FALSE);
	if (!xdr_netobj(xdrs, &objp->oh))
		return (FALSE);
	if (!xdr_int(xdrs, &objp->svid))
		return (FALSE);
	if (!xdr_u_int(xdrs, &objp->l_offset))
		return (FALSE);
	if (!xdr_u_int(xdrs, &objp->l_len))
		return (FALSE);
	return (TRUE);
}