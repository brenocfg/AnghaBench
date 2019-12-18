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
typedef  scalar_t__ u_long ;
typedef  int /*<<< orphan*/  u_int ;
struct TYPE_3__ {scalar_t__ x_base; scalar_t__ x_private; } ;
typedef  TYPE_1__ XDR ;

/* Variables and functions */

__attribute__((used)) static u_int
xdrmem_getpos(XDR *xdrs)
{

	/* XXX w/64-bit pointers, u_int not enough! */
	return (u_int)((u_long)xdrs->x_private - (u_long)xdrs->x_base);
}