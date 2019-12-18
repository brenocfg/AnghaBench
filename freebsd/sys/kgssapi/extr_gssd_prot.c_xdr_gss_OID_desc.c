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
struct TYPE_3__ {char* elements; int /*<<< orphan*/  length; } ;
typedef  TYPE_1__ gss_OID_desc ;
typedef  int /*<<< orphan*/  bool_t ;
typedef  int /*<<< orphan*/  XDR ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  xdr_bytes (int /*<<< orphan*/ *,char**,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

bool_t
xdr_gss_OID_desc(XDR *xdrs, gss_OID_desc *oid)
{
	char *val;
	u_int len;

	len = oid->length;
	val = oid->elements;
	if (!xdr_bytes(xdrs, &val, &len, ~0))
		return (FALSE);
	oid->length = len;
	oid->elements = val;

	return (TRUE);
}