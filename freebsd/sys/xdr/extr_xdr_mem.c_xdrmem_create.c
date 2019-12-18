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
typedef  int /*<<< orphan*/  int32_t ;
typedef  enum xdr_op { ____Placeholder_xdr_op } xdr_op ;
struct TYPE_3__ {int x_op; char* x_private; char* x_base; int /*<<< orphan*/  x_handy; int /*<<< orphan*/ * x_ops; } ;
typedef  TYPE_1__ XDR ;

/* Variables and functions */
 int /*<<< orphan*/  xdrmem_ops_aligned ; 
 int /*<<< orphan*/  xdrmem_ops_unaligned ; 

void
xdrmem_create(XDR *xdrs, char *addr, u_int size, enum xdr_op op)
{

	xdrs->x_op = op;
	xdrs->x_ops = ((unsigned long)addr & (sizeof(int32_t) - 1))
	    ? &xdrmem_ops_unaligned : &xdrmem_ops_aligned;
	xdrs->x_private = xdrs->x_base = addr;
	xdrs->x_handy = size;
}