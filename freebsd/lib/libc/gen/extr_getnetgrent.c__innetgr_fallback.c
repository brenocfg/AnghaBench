#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {void* member_0; int member_1; } ;
typedef  TYPE_1__ ns_src ;

/* Variables and functions */
 int ERANGE ; 
 size_t NGRP_STORAGE_INITIAL ; 
 size_t NGRP_STORAGE_MAX ; 
 int /*<<< orphan*/  NSDB_NETGROUP ; 
 int NS_NOTFOUND ; 
 int NS_RETURN ; 
 int NS_SUCCESS ; 
 int NS_UNAVAIL ; 
 int _nsdispatch (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,TYPE_1__ const*,...) ; 
 int /*<<< orphan*/  endnetgrent_dtab ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  getnetgrent_dtab ; 
 char* malloc (size_t) ; 
 char* reallocf (char*,size_t) ; 
 int /*<<< orphan*/  setnetgrent_dtab ; 
 scalar_t__ strcmp (char const*,char*) ; 

__attribute__((used)) static int
_innetgr_fallback(void *retval, void *mdata, const char *group, const char *host,
    const char *user, const char *dom)
{
	const ns_src src[] = {
		{ mdata, NS_SUCCESS },
		{ NULL, 0 },
	};
	char *h, *u, *d;
	char *buf;
	size_t bufsize;
	int rv, ret_errno;

	if (group == NULL || group[0] == '\0')
		return (NS_RETURN);

	bufsize = NGRP_STORAGE_INITIAL;
	buf = malloc(bufsize);
	if (buf == NULL)
		return (NS_UNAVAIL);

	*(int *)retval = 0;

	(void)_nsdispatch(NULL, setnetgrent_dtab, NSDB_NETGROUP, "setnetgrent",
	    src, group);

	for (;;) {
		do {
			ret_errno = 0;
			rv = _nsdispatch(NULL, getnetgrent_dtab, NSDB_NETGROUP,
			    "getnetgrent_r", src, &h, &u, &d, buf, bufsize,
			    &ret_errno);
			if (rv != NS_SUCCESS && ret_errno == ERANGE) {
				bufsize *= 2;
				if (bufsize > NGRP_STORAGE_MAX ||
				    (buf = reallocf(buf, bufsize)) == NULL)
					goto out;
			}
		} while (rv != NS_SUCCESS && ret_errno == ERANGE);

		if (rv != NS_SUCCESS) {
			if (rv == NS_NOTFOUND && ret_errno == 0)
				rv = NS_SUCCESS;
			break;
		}

		if ((host == NULL || h == NULL || strcmp(host, h) == 0) &&
		    (user == NULL || u == NULL || strcmp(user, u) == 0) &&
		    (dom == NULL || d == NULL || strcmp(dom, d) == 0)) {
			*(int *)retval = 1;
			break;
		}
	}

out:
	free(buf);
	(void)_nsdispatch(NULL, endnetgrent_dtab, NSDB_NETGROUP, "endnetgrent",
	    src);
	return (rv);
}