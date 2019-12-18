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
typedef  int u_long ;
struct r_rmtcall_args {scalar_t__ rmt_localvers; int /*<<< orphan*/  rmt_args; int /*<<< orphan*/  rmt_uaddr; } ;
typedef  scalar_t__ bool_t ;
typedef  int /*<<< orphan*/  XDR ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 scalar_t__ PMAPVERS ; 
 scalar_t__ RPCBVERS ; 
 scalar_t__ RPCBVERS4 ; 
 scalar_t__ TRUE ; 
 int sscanf (int /*<<< orphan*/ ,char*,int*,int*,int*,int*,int*,int*) ; 
 scalar_t__ xdr_encap_parms (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ xdr_u_long (int /*<<< orphan*/ *,int*) ; 
 scalar_t__ xdr_wrapstring (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool_t
xdr_rmtcall_result(XDR *xdrs, struct r_rmtcall_args *cap)
{
	bool_t result;

#ifdef PORTMAP
	if (cap->rmt_localvers == PMAPVERS) {
		int h1, h2, h3, h4, p1, p2;
		u_long port;

		/* interpret the universal address for TCP/IP */
		if (sscanf(cap->rmt_uaddr, "%d.%d.%d.%d.%d.%d",
			&h1, &h2, &h3, &h4, &p1, &p2) != 6)
			return (FALSE);
		port = ((p1 & 0xff) << 8) + (p2 & 0xff);
		result = xdr_u_long(xdrs, &port);
	} else
#endif
		if ((cap->rmt_localvers == RPCBVERS) ||
		    (cap->rmt_localvers == RPCBVERS4)) {
		result = xdr_wrapstring(xdrs, &(cap->rmt_uaddr));
	} else {
		return (FALSE);
	}
	if (result == TRUE)
		return (xdr_encap_parms(xdrs, &(cap->rmt_args)));
	return (FALSE);
}