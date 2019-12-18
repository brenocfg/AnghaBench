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
struct iovec {size_t iov_len; scalar_t__ iov_base; } ;
struct TYPE_3__ {int /*<<< orphan*/  ms_name; } ;
typedef  TYPE_1__ modstat_t ;

/* Variables and functions */
 int /*<<< orphan*/  MODCTL_STAT ; 
 int /*<<< orphan*/  atf_tc_fail (char*) ; 
 int /*<<< orphan*/  check_permission () ; 
 int errno ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  free (scalar_t__) ; 
 scalar_t__ malloc (size_t) ; 
 scalar_t__ modctl (int /*<<< orphan*/ ,struct iovec*) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char const*) ; 
 char* strerror (int) ; 

__attribute__((used)) static bool
get_modstat_info(const char *name, modstat_t *msdest)
{
	bool found;
	size_t len;
	struct iovec iov;
	modstat_t *ms;

	check_permission();
	for (len = 4096; ;) {
		iov.iov_base = malloc(len);
		iov.iov_len = len;

		errno = 0;

		if (modctl(MODCTL_STAT, &iov) != 0) {
			int err = errno;
			fprintf(stderr, "modctl(MODCTL_STAT) failed: %s\n",
			    strerror(err));
			atf_tc_fail("Failed to query module status");
		}
		if (len >= iov.iov_len)
			break;
		free(iov.iov_base);
		len = iov.iov_len;
	}

	found = false;
	len = iov.iov_len / sizeof(modstat_t);
	for (ms = (modstat_t *)iov.iov_base; len != 0 && !found;
	    ms++, len--) {
		if (strcmp(ms->ms_name, name) == 0) {
			if (msdest != NULL)
				*msdest = *ms;
			found = true;
		}
	}

	free(iov.iov_base);

	return found;
}