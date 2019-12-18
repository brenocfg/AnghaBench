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
typedef  enum xdr_op { ____Placeholder_xdr_op } xdr_op ;
struct TYPE_3__ {int x_op; scalar_t__ x_base; scalar_t__ x_handy; int /*<<< orphan*/ * x_private; int /*<<< orphan*/ * x_ops; } ;
typedef  TYPE_1__ XDR ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  xdrstdio_ops ; 

void
xdrstdio_create(XDR *xdrs, FILE *file, enum xdr_op op)
{

	xdrs->x_op = op;
	xdrs->x_ops = &xdrstdio_ops;
	xdrs->x_private = file;
	xdrs->x_handy = 0;
	xdrs->x_base = 0;
}