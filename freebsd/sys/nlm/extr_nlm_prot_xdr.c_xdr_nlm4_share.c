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
struct TYPE_3__ {int /*<<< orphan*/  access; int /*<<< orphan*/  mode; int /*<<< orphan*/  oh; int /*<<< orphan*/  fh; int /*<<< orphan*/  caller_name; } ;
typedef  TYPE_1__ nlm4_share ;
typedef  int /*<<< orphan*/  bool_t ;
typedef  int /*<<< orphan*/  XDR ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  MAXNAMELEN ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  xdr_fsh_access (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xdr_fsh_mode (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xdr_netobj (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xdr_string (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

bool_t
xdr_nlm4_share(XDR *xdrs, nlm4_share *objp)
{

	if (!xdr_string(xdrs, &objp->caller_name, MAXNAMELEN))
		return (FALSE);
	if (!xdr_netobj(xdrs, &objp->fh))
		return (FALSE);
	if (!xdr_netobj(xdrs, &objp->oh))
		return (FALSE);
	if (!xdr_fsh_mode(xdrs, &objp->mode))
		return (FALSE);
	if (!xdr_fsh_access(xdrs, &objp->access))
		return (FALSE);
	return (TRUE);
}