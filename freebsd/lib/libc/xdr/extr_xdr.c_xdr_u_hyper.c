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
typedef  int /*<<< orphan*/  u_longlong_t ;
typedef  int /*<<< orphan*/  u_int64_t ;
typedef  int /*<<< orphan*/  bool_t ;
typedef  int /*<<< orphan*/  XDR ;

/* Variables and functions */
 int /*<<< orphan*/  xdr_u_int64_t (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

bool_t
xdr_u_hyper(XDR *xdrs, u_longlong_t *ullp)
{

	/*
	 * Don't bother open-coding this; it's a fair amount of code.  Just
	 * call xdr_u_int64_t().
	 */
	return (xdr_u_int64_t(xdrs, (u_int64_t *)ullp));
}