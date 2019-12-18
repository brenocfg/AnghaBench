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
 int ERANGE ; 
 size_t NGRP_STORAGE_INITIAL ; 
 size_t NGRP_STORAGE_MAX ; 
 int /*<<< orphan*/  NSDB_NETGROUP ; 
 int NS_SUCCESS ; 
 int _nsdispatch (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char**,char**,char**,char*,size_t,int*) ; 
 int /*<<< orphan*/  defaultsrc ; 
 int errno ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  getnetgrent_dtab ; 
 char* malloc (size_t) ; 
 char* reallocf (char*,size_t) ; 

int
getnetgrent(char **hostp, char **userp, char **domp)
{
	static char *ngrp_storage;
	static size_t ngrp_storage_size;
	int ret_errno, rv;

	if (ngrp_storage == NULL) {
		ngrp_storage_size = NGRP_STORAGE_INITIAL;
		ngrp_storage = malloc(ngrp_storage_size);
		if (ngrp_storage == NULL)
			return (0);
	}

	do {
		ret_errno = 0;
		rv = _nsdispatch(NULL, getnetgrent_dtab, NSDB_NETGROUP,
		    "getnetgrent_r", defaultsrc, hostp, userp, domp,
		    ngrp_storage, ngrp_storage_size, &ret_errno);
		if (rv != NS_SUCCESS && ret_errno == ERANGE) {
			ngrp_storage_size *= 2;
			if (ngrp_storage_size > NGRP_STORAGE_MAX) {
				free(ngrp_storage);
				ngrp_storage = NULL;
				errno = ERANGE;
				return (0);
			}
			ngrp_storage = reallocf(ngrp_storage,
			    ngrp_storage_size);
			if (ngrp_storage == NULL)
				return (0);
		}
	} while (rv != NS_SUCCESS && ret_errno == ERANGE);

	if (rv == NS_SUCCESS) {
		return (1);
	} else {
		errno = ret_errno;
		return (0);
	}
}