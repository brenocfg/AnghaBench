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
typedef  int /*<<< orphan*/  bool_t ;
struct TYPE_3__ {scalar_t__ x_handy; char* x_private; } ;
typedef  TYPE_1__ XDR ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  memmove (char*,char const*,scalar_t__) ; 

__attribute__((used)) static bool_t
xdrmem_putbytes(XDR *xdrs, const char *addr, u_int len)
{

	if (xdrs->x_handy < len)
		return (FALSE);
	xdrs->x_handy -= len;
	memmove(xdrs->x_private, addr, len);
	xdrs->x_private = (char *)xdrs->x_private + len;
	return (TRUE);
}