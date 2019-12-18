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
struct group {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NSDB_GROUP ; 
 int NS_SUCCESS ; 
 int _nsdispatch (struct group**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,struct group*,char*,size_t,int*) ; 
 int /*<<< orphan*/  defaultsrc ; 
 int /*<<< orphan*/  getgrent_r_dtab ; 

int
getgrent_r(struct group *grp, char *buffer, size_t bufsize,
    struct group **result)
{
	int	rv, ret_errno;

	ret_errno = 0;
	*result = NULL;
	rv = _nsdispatch(result, getgrent_r_dtab, NSDB_GROUP, "getgrent_r", defaultsrc,
	    grp, buffer, bufsize, &ret_errno);
	if (rv == NS_SUCCESS)
		return (0);
	else
		return (ret_errno);
}