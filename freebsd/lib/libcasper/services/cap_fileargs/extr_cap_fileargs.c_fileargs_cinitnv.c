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
typedef  int /*<<< orphan*/  nvlist_t ;
typedef  int /*<<< orphan*/  fileargs_t ;
typedef  int /*<<< orphan*/  cap_channel_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cap_close (int /*<<< orphan*/ *) ; 
 int cap_limit_set (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * cap_service_open (int /*<<< orphan*/ *,char*) ; 
 int errno ; 
 int /*<<< orphan*/ * fileargs_create (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  nvlist_destroy (int /*<<< orphan*/ *) ; 
 int nvlist_get_number (int /*<<< orphan*/ *,char*) ; 

fileargs_t *
fileargs_cinitnv(cap_channel_t *cas, nvlist_t *limits)
{
	cap_channel_t *chann;
	fileargs_t *fa;
	int serrno, ret;
	int flags, operations;

	assert(cas != NULL);

	if (limits == NULL) {
		return (fileargs_create(NULL, 0));
	}

	chann = NULL;
	fa = NULL;

	chann = cap_service_open(cas, "system.fileargs");
	if (chann == NULL) {
		nvlist_destroy(limits);
		return (NULL);
	}

	flags = nvlist_get_number(limits, "flags");
	operations = nvlist_get_number(limits, "operations");

	/* Limits are consumed no need to free them. */
	ret = cap_limit_set(chann, limits);
	if (ret < 0)
		goto out;

	fa = fileargs_create(chann, flags);
	if (fa == NULL)
		goto out;

	return (fa);
out:
	serrno = errno;
	if (chann != NULL)
		cap_close(chann);
	errno = serrno;
	return (NULL);
}