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

/* Variables and functions */
 int /*<<< orphan*/  NSDB_NETGROUP ; 
 int /*<<< orphan*/  _nsdispatch (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  defaultsrc ; 
 int /*<<< orphan*/  setnetgrent_dtab ; 

void
setnetgrent(const char *netgroup)
{

	(void)_nsdispatch(NULL, setnetgrent_dtab, NSDB_NETGROUP, "setnetgrent",
	    defaultsrc, netgroup);
}