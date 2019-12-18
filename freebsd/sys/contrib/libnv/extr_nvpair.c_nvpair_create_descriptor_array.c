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
typedef  int /*<<< orphan*/  value ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  nvpair_t ;
typedef  int /*<<< orphan*/  int64_t ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ERRNO_RESTORE () ; 
 int /*<<< orphan*/  ERRNO_SAVE () ; 
 int /*<<< orphan*/  ERRNO_SET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  F_DUPFD_CLOEXEC ; 
 int /*<<< orphan*/  NV_TYPE_DESCRIPTOR_ARRAY ; 
 int /*<<< orphan*/  close (int) ; 
 int fcntl (int const,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nv_free (int*) ; 
 int* nv_malloc (int) ; 
 int /*<<< orphan*/ * nvpair_allocv (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,size_t) ; 

nvpair_t *
nvpair_create_descriptor_array(const char *name, const int *value,
    size_t nitems)
{
	unsigned int ii;
	nvpair_t *nvp;
	int *fds;

	if (value == NULL) {
		ERRNO_SET(EINVAL);
		return (NULL);
	}

	nvp = NULL;

	fds = nv_malloc(sizeof(value[0]) * nitems);
	if (fds == NULL)
		return (NULL);
	for (ii = 0; ii < nitems; ii++) {
		if (value[ii] == -1) {
			fds[ii] = -1;
		} else {
			fds[ii] = fcntl(value[ii], F_DUPFD_CLOEXEC, 0);
			if (fds[ii] == -1)
				goto fail;
		}
	}

	nvp = nvpair_allocv(name, NV_TYPE_DESCRIPTOR_ARRAY,
	    (uint64_t)(uintptr_t)fds, sizeof(int64_t) * nitems, nitems);

fail:
	if (nvp == NULL) {
		ERRNO_SAVE();
		for (; ii > 0; ii--) {
			if (fds[ii - 1] != -1)
				close(fds[ii - 1]);
		}
		nv_free(fds);
		ERRNO_RESTORE();
	}

	return (nvp);
}