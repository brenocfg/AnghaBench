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
struct TYPE_4__ {int /*<<< orphan*/  deskey; } ;
struct TYPE_5__ {int status; TYPE_1__ cryptkeyres_u; } ;
typedef  TYPE_2__ cryptkeyres ;
typedef  int /*<<< orphan*/  bool_t ;
typedef  int /*<<< orphan*/  XDR ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
#define  KEY_SUCCESS 128 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  xdr_des_block (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xdr_keystatus (int /*<<< orphan*/ *,int*) ; 

bool_t
xdr_cryptkeyres(register XDR *xdrs, cryptkeyres *objp)
{

	if (!xdr_keystatus(xdrs, &objp->status))
		return (FALSE);
	switch (objp->status) {
	case KEY_SUCCESS:
		if (!xdr_des_block(xdrs, &objp->cryptkeyres_u.deskey))
			return (FALSE);
		break;
	default:
		break;
	}
	return (TRUE);
}