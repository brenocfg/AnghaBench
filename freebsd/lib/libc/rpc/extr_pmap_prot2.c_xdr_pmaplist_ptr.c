#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct pmaplist {int dummy; } ;
typedef  int /*<<< orphan*/  bool_t ;
typedef  int /*<<< orphan*/  XDR ;

/* Variables and functions */
 int /*<<< orphan*/  xdr_pmaplist (int /*<<< orphan*/ *,struct pmaplist**) ; 

bool_t
xdr_pmaplist_ptr(XDR *xdrs, struct pmaplist *rp)
{
	return xdr_pmaplist(xdrs, (struct pmaplist **)(void *)rp);
}