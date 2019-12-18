#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  xdrproc_t ;
struct TYPE_4__ {int /*<<< orphan*/  gids_len; int /*<<< orphan*/ * gids_val; } ;
struct TYPE_5__ {TYPE_1__ gids; int /*<<< orphan*/  gid; int /*<<< orphan*/  uid; } ;
typedef  TYPE_2__ unixcred ;
typedef  int /*<<< orphan*/  u_int ;
typedef  int /*<<< orphan*/  bool_t ;
typedef  int /*<<< orphan*/  XDR ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  MAXGIDS ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  xdr_array (int /*<<< orphan*/ *,char**,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xdr_u_int (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

bool_t
xdr_unixcred(register XDR *xdrs, unixcred *objp)
{
	u_int **pgids_val;

	if (!xdr_u_int(xdrs, &objp->uid))
		return (FALSE);
	if (!xdr_u_int(xdrs, &objp->gid))
		return (FALSE);
	pgids_val = &objp->gids.gids_val;
	if (!xdr_array(xdrs, (char **) pgids_val, (u_int *) &objp->gids.gids_len, MAXGIDS,
		sizeof (u_int), (xdrproc_t) xdr_u_int))
		return (FALSE);
	return (TRUE);
}