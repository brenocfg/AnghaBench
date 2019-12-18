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
struct info {long retval; } ;
typedef  scalar_t__ caddr_t ;
typedef  int /*<<< orphan*/  bool_t ;
typedef  int /*<<< orphan*/  XDR ;

/* Variables and functions */
 int /*<<< orphan*/  xdr_long (int /*<<< orphan*/ *,long*) ; 

__attribute__((used)) static bool_t
xdr_retval(XDR *xdrsp, caddr_t cp)
{
	struct info *ifp = (struct info *)cp;
	long val;

	val = ifp->retval;
	return (xdr_long(xdrsp, &val));
}