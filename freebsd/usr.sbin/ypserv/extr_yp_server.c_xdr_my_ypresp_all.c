#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  val; int /*<<< orphan*/  key; int /*<<< orphan*/  stat; } ;
struct TYPE_7__ {TYPE_1__ val; } ;
struct TYPE_8__ {scalar_t__ more; TYPE_2__ ypresp_all_u; } ;
typedef  TYPE_3__ ypresp_all ;
typedef  scalar_t__ bool_t ;
typedef  int /*<<< orphan*/  XDR ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  YP_TRUE ; 
 int /*<<< orphan*/  xdr_ypresp_all (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  yp_nextbykey (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool_t
xdr_my_ypresp_all(register XDR *xdrs, ypresp_all *objp)
{
	while (1) {
		/* Get a record. */
		if ((objp->ypresp_all_u.val.stat =
			yp_nextbykey(&objp->ypresp_all_u.val.key,
				     &objp->ypresp_all_u.val.val)) == YP_TRUE) {
			objp->more = TRUE;
		} else {
			objp->more = FALSE;
		}

		/* Serialize. */
		if (!xdr_ypresp_all(xdrs, objp))
			return(FALSE);
		if (objp->more == FALSE)
			return(TRUE);
	}
}