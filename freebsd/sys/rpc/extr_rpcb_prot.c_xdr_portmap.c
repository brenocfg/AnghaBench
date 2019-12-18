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
struct portmap {int /*<<< orphan*/  pm_port; int /*<<< orphan*/  pm_prot; int /*<<< orphan*/  pm_vers; int /*<<< orphan*/  pm_prog; } ;
typedef  scalar_t__ bool_t ;
typedef  int /*<<< orphan*/  XDR ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 scalar_t__ xdr_u_long (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

bool_t
xdr_portmap(XDR *xdrs, struct portmap *regs)
{

	if (xdr_u_long(xdrs, &regs->pm_prog) &&
		xdr_u_long(xdrs, &regs->pm_vers) &&
		xdr_u_long(xdrs, &regs->pm_prot))
		return (xdr_u_long(xdrs, &regs->pm_port));
	return (FALSE);
}