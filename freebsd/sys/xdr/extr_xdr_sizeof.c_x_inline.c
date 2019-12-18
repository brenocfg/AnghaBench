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
typedef  void* caddr_t ;
struct TYPE_3__ {scalar_t__ x_op; int /*<<< orphan*/ * x_private; int /*<<< orphan*/  x_handy; void* x_base; } ;
typedef  TYPE_1__ XDR ;

/* Variables and functions */
 int /*<<< orphan*/  M_RPC ; 
 int /*<<< orphan*/  M_WAITOK ; 
 scalar_t__ XDR_ENCODE ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ malloc (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int32_t *
x_inline(XDR *xdrs, u_int len)
{

	if (len == 0) {
		return (NULL);
	}
	if (xdrs->x_op != XDR_ENCODE) {
		return (NULL);
	}
	if (len < (u_int)(uintptr_t)xdrs->x_base) {
		/* x_private was already allocated */
		xdrs->x_handy += len;
		return ((int32_t *) xdrs->x_private);
	} else {
		/* Free the earlier space and allocate new area */
		if (xdrs->x_private)
			free(xdrs->x_private, M_RPC);
		if ((xdrs->x_private = (caddr_t) malloc(len, M_RPC, M_WAITOK)) == NULL) {
			xdrs->x_base = 0;
			return (NULL);
		}
		xdrs->x_base = (caddr_t)(uintptr_t) len;
		xdrs->x_handy += len;
		return ((int32_t *) xdrs->x_private);
	}
}