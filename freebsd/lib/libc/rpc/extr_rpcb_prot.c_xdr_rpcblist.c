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
typedef  int /*<<< orphan*/  rpcblist_ptr ;
typedef  int /*<<< orphan*/  bool_t ;
typedef  int /*<<< orphan*/  XDR ;
typedef  int /*<<< orphan*/  RPCBLIST ;

/* Variables and functions */
 int /*<<< orphan*/  xdr_rpcblist_ptr (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

bool_t
xdr_rpcblist(XDR *xdrs, RPCBLIST **rp)
{
	bool_t	dummy;

	dummy = xdr_rpcblist_ptr(xdrs, (rpcblist_ptr *)rp);
	return (dummy);
}