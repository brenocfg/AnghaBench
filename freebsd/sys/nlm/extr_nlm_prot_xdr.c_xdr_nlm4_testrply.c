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
struct TYPE_4__ {int /*<<< orphan*/  holder; } ;
struct TYPE_5__ {int stat; TYPE_1__ nlm4_testrply_u; } ;
typedef  TYPE_2__ nlm4_testrply ;
typedef  int /*<<< orphan*/  bool_t ;
typedef  int /*<<< orphan*/  XDR ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
#define  nlm_denied 128 
 int /*<<< orphan*/  xdr_nlm4_holder (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xdr_nlm4_stats (int /*<<< orphan*/ *,int*) ; 

bool_t
xdr_nlm4_testrply(XDR *xdrs, nlm4_testrply *objp)
{

	if (!xdr_nlm4_stats(xdrs, &objp->stat))
		return (FALSE);
	switch (objp->stat) {
	case nlm_denied:
		if (!xdr_nlm4_holder(xdrs, &objp->nlm4_testrply_u.holder))
			return (FALSE);
		break;
	default:
		break;
	}
	return (TRUE);
}