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
struct TYPE_4__ {int /*<<< orphan*/  knet; } ;
struct TYPE_5__ {int status; TYPE_1__ key_netstres_u; } ;
typedef  TYPE_2__ key_netstres ;
typedef  int /*<<< orphan*/  bool_t ;
typedef  int /*<<< orphan*/  XDR ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
#define  KEY_SUCCESS 128 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  xdr_key_netstarg (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xdr_keystatus (int /*<<< orphan*/ *,int*) ; 

bool_t
xdr_key_netstres(register XDR *xdrs, key_netstres *objp)
{

	if (!xdr_keystatus(xdrs, &objp->status))
		return (FALSE);
	switch (objp->status) {
	case KEY_SUCCESS:
		if (!xdr_key_netstarg(xdrs, &objp->key_netstres_u.knet))
			return (FALSE);
		break;
	default:
		break;
	}
	return (TRUE);
}