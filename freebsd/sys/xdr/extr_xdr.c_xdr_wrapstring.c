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
typedef  int /*<<< orphan*/  bool_t ;
typedef  int /*<<< orphan*/  XDR ;

/* Variables and functions */
 int /*<<< orphan*/  RPC_MAXDATASIZE ; 
 int /*<<< orphan*/  xdr_string (int /*<<< orphan*/ *,char**,int /*<<< orphan*/ ) ; 

bool_t
xdr_wrapstring(XDR *xdrs, char **cpp)
{
	return xdr_string(xdrs, cpp, RPC_MAXDATASIZE);
}