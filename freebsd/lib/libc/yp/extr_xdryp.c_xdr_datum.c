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
typedef  int /*<<< orphan*/  u_int ;
struct TYPE_3__ {int /*<<< orphan*/  dsize; int /*<<< orphan*/  dptr; } ;
typedef  TYPE_1__ datum ;
typedef  int /*<<< orphan*/  bool_t ;
typedef  int /*<<< orphan*/  XDR ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  YPMAXRECORD ; 
 int /*<<< orphan*/  xdr_bytes (int /*<<< orphan*/ *,char**,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

bool_t
xdr_datum(XDR *xdrs, datum *objp)
{
	if (!xdr_bytes(xdrs, (char **)&objp->dptr, (u_int *)&objp->dsize, YPMAXRECORD)) {
		return (FALSE);
	}
	return (TRUE);
}