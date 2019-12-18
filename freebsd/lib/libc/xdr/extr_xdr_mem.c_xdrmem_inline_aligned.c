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
typedef  scalar_t__ u_int ;
typedef  int /*<<< orphan*/  int32_t ;
struct TYPE_3__ {scalar_t__ x_handy; char* x_private; } ;
typedef  TYPE_1__ XDR ;

/* Variables and functions */

__attribute__((used)) static int32_t *
xdrmem_inline_aligned(XDR *xdrs, u_int len)
{
	int32_t *buf = NULL;

	if (xdrs->x_handy >= len) {
		xdrs->x_handy -= len;
		buf = (int32_t *)xdrs->x_private;
		xdrs->x_private = (char *)xdrs->x_private + len;
	}
	return (buf);
}