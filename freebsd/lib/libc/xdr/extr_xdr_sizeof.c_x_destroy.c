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
struct TYPE_3__ {int /*<<< orphan*/ * x_private; scalar_t__ x_base; scalar_t__ x_handy; } ;
typedef  TYPE_1__ XDR ;

/* Variables and functions */
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
x_destroy(XDR *xdrs)
{
	xdrs->x_handy = 0;
	xdrs->x_base = 0;
	if (xdrs->x_private) {
		free(xdrs->x_private);
		xdrs->x_private = NULL;
	}
	return;
}