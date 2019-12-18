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
typedef  int /*<<< orphan*/  xdrproc_t ;
typedef  int /*<<< orphan*/  u_int ;
struct TYPE_3__ {scalar_t__ elements; int /*<<< orphan*/  count; } ;
typedef  TYPE_1__ gss_OID_set_desc ;
typedef  int /*<<< orphan*/  gss_OID_desc ;
typedef  scalar_t__ gss_OID ;
typedef  scalar_t__ caddr_t ;
typedef  int /*<<< orphan*/  bool_t ;
typedef  int /*<<< orphan*/  XDR ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  xdr_array (int /*<<< orphan*/ *,scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 scalar_t__ xdr_gss_OID_desc ; 

bool_t
xdr_gss_OID_set_desc(XDR *xdrs, gss_OID_set_desc *set)
{
	caddr_t addr;
	u_int len;

	len = set->count;
	addr = (caddr_t) set->elements;
	if (!xdr_array(xdrs, &addr, &len, ~0, sizeof(gss_OID_desc),
		(xdrproc_t) xdr_gss_OID_desc))
		return (FALSE);
	set->count = len;
	set->elements = (gss_OID) addr;

	return (TRUE);
}