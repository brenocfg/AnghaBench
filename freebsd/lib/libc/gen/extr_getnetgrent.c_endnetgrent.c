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
 int /*<<< orphan*/  _nsdispatch (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  defaultsrc ; 
 int /*<<< orphan*/  endnetgrent_dtab ; 

void
endnetgrent(void)
{

	(void)_nsdispatch(NULL, endnetgrent_dtab, NSDB_NETGROUP, "endnetgrent",
	    defaultsrc);
}