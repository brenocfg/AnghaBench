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
 int NS_SUCCESS ; 
 int _nsdispatch (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char**,char**,char**,char*,size_t,int*) ; 
 int /*<<< orphan*/  defaultsrc ; 
 int errno ; 
 int /*<<< orphan*/  getnetgrent_dtab ; 

int
getnetgrent_r(char **hostp, char **userp, char **domp, char *buf, size_t bufsize)
{
	int rv, ret_errno;

	ret_errno = 0;
	rv = _nsdispatch(NULL, getnetgrent_dtab, NSDB_NETGROUP, "getnetgrent_r",
	    defaultsrc, hostp, userp, domp, buf, bufsize, &ret_errno);
	if (rv == NS_SUCCESS) {
		return (1);
	} else {
		errno = ret_errno;
		return (0);
	}
}