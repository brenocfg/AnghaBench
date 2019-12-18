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
typedef  scalar_t__ uint8_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  nvlist_t ;
typedef  int /*<<< orphan*/  cap_channel_t ;

/* Variables and functions */
 scalar_t__ CAP_SYSCTL_READ ; 
 scalar_t__ CAP_SYSCTL_WRITE ; 
 int /*<<< orphan*/ * cap_xfer_nvlist (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ dnvlist_get_number (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int errno ; 
 int /*<<< orphan*/  memcpy (void*,scalar_t__ const*,size_t) ; 
 int /*<<< orphan*/  nvlist_add_binary (int /*<<< orphan*/ *,char*,void const*,size_t) ; 
 int /*<<< orphan*/  nvlist_add_null (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  nvlist_add_number (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvlist_destroy (int /*<<< orphan*/ *) ; 
 scalar_t__* nvlist_get_binary (int /*<<< orphan*/ *,char*,size_t*) ; 
 scalar_t__ nvlist_get_number (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static int
do_sysctl(cap_channel_t *chan, nvlist_t *nvl, void *oldp, size_t *oldlenp,
    const void *newp, size_t newlen)
{
	const uint8_t *retoldp;
	size_t oldlen;
	int error;
	uint8_t operation;

	operation = 0;
	if (oldlenp != NULL)
		operation |= CAP_SYSCTL_READ;
	if (newp != NULL)
		operation |= CAP_SYSCTL_WRITE;
	nvlist_add_number(nvl, "operation", (uint64_t)operation);
	if (oldp == NULL && oldlenp != NULL)
		nvlist_add_null(nvl, "justsize");
	else if (oldlenp != NULL)
		nvlist_add_number(nvl, "oldlen", (uint64_t)*oldlenp);
	if (newp != NULL)
		nvlist_add_binary(nvl, "newp", newp, newlen);

	nvl = cap_xfer_nvlist(chan, nvl);
	if (nvl == NULL)
		return (-1);
	error = (int)dnvlist_get_number(nvl, "error", 0);
	if (error != 0) {
		nvlist_destroy(nvl);
		errno = error;
		return (-1);
	}

	if (oldp == NULL && oldlenp != NULL) {
		*oldlenp = (size_t)nvlist_get_number(nvl, "oldlen");
	} else if (oldp != NULL) {
		retoldp = nvlist_get_binary(nvl, "oldp", &oldlen);
		memcpy(oldp, retoldp, oldlen);
		if (oldlenp != NULL)
			*oldlenp = oldlen;
	}

	nvlist_destroy(nvl);

	return (0);
}