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
typedef  int /*<<< orphan*/  u_int32_t ;
typedef  int /*<<< orphan*/  int32_t ;
typedef  int /*<<< orphan*/  bool_t ;
struct TYPE_3__ {int x_handy; char* x_private; } ;
typedef  TYPE_1__ XDR ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 long ntohl (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool_t
xdrmem_getlong_aligned(XDR *xdrs, long *lp)
{

	if (xdrs->x_handy < sizeof(int32_t))
		return (FALSE);
	xdrs->x_handy -= sizeof(int32_t);
	*lp = ntohl(*(u_int32_t *)xdrs->x_private);
	xdrs->x_private = (char *)xdrs->x_private + sizeof(int32_t);
	return (TRUE);
}