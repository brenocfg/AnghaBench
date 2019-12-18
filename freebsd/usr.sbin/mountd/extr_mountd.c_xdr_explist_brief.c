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
typedef  int /*<<< orphan*/  caddr_t ;
typedef  int /*<<< orphan*/  XDR ;

/* Variables and functions */
 int xdr_explist_common (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
xdr_explist_brief(XDR *xdrsp, caddr_t cp)
{

	return xdr_explist_common(xdrsp, cp, 1);
}