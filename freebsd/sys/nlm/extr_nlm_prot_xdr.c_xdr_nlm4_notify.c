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
struct TYPE_3__ {int /*<<< orphan*/  state; int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ nlm4_notify ;
typedef  int /*<<< orphan*/  bool_t ;
typedef  int /*<<< orphan*/  XDR ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  MAXNAMELEN ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  xdr_int32_t (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xdr_string (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

bool_t
xdr_nlm4_notify(XDR *xdrs, nlm4_notify *objp)
{

	if (!xdr_string(xdrs, &objp->name, MAXNAMELEN))
		return (FALSE);
	if (!xdr_int32_t(xdrs, &objp->state))
		return (FALSE);
	return (TRUE);
}