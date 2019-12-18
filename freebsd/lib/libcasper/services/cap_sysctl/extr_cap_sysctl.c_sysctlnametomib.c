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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  nvlist_t ;
typedef  int /*<<< orphan*/  cap_channel_t ;

/* Variables and functions */
 int /*<<< orphan*/ * cap_xfer_nvlist (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ dnvlist_get_number (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int errno ; 
 int /*<<< orphan*/  memcpy (int*,void const*,size_t) ; 
 int /*<<< orphan*/  nvlist_add_number (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvlist_add_string (int /*<<< orphan*/ *,char*,char const*) ; 
 int /*<<< orphan*/ * nvlist_create (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvlist_destroy (int /*<<< orphan*/ *) ; 
 void* nvlist_get_binary (int /*<<< orphan*/ *,char*,size_t*) ; 

int
cap_sysctlnametomib(cap_channel_t *chan, const char *name, int *mibp,
    size_t *sizep)
{
	nvlist_t *req;
	const void *mib;
	size_t mibsz;
	int error;

	req = nvlist_create(0);
	nvlist_add_string(req, "cmd", "sysctlnametomib");
	nvlist_add_string(req, "name", name);
	nvlist_add_number(req, "operation", 0);
	nvlist_add_number(req, "size", (uint64_t)*sizep);

	req = cap_xfer_nvlist(chan, req);
	if (req == NULL)
		return (-1);
	error = (int)dnvlist_get_number(req, "error", 0);
	if (error != 0) {
		nvlist_destroy(req);
		errno = error;
		return (-1);
	}

	mib = nvlist_get_binary(req, "mib", &mibsz);
	*sizep = mibsz / sizeof(int);

	memcpy(mibp, mib, mibsz); 

	nvlist_destroy(req);

	return (0);
}