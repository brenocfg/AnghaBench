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
 scalar_t__ ENOMEM ; 
 size_t SD_FACTOR ; 
 size_t SD_MARGIN ; 
 int SD_MAXMIB ; 
 int SD_NTRIES ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  error (char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ malloc (size_t) ; 
 int sysctl (int*,size_t,char*,size_t*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int sysctlnametomib (char const*,int*,size_t*) ; 

char *
sysctl_dynread(const char *n, size_t *szp)
{
	char   *rv = NULL;
	int    mib[SD_MAXMIB];
	size_t mibsz = SD_MAXMIB;
	size_t mrg = SD_MARGIN;
	size_t sz;
	int i;

	/* cache the MIB */
	if (sysctlnametomib(n, mib, &mibsz) == -1) {
		if (errno == ENOMEM) {
			error("XXX: SD_MAXMIB too small, please bump!");
		}
		return NULL;
	}
	for (i = 0; i < SD_NTRIES; i++) {
		/* get needed buffer size */
		if (sysctl(mib, mibsz, NULL, &sz, NULL, 0) == -1)
			break;
		sz += sz * mrg / 100;
		if ((rv = (char *)malloc(sz)) == NULL) {
			error("Out of memory!");
			return NULL;
		}
		if (sysctl(mib, mibsz, rv, &sz, NULL, 0) == -1) {
			free(rv);
			rv = NULL;
			if (errno == ENOMEM) {
				mrg += mrg * SD_FACTOR / 100;
			} else
				break;
		} else {
			/* success */
			if (szp != NULL)
				*szp = sz;
			break;
		}
	}

	return rv;
}