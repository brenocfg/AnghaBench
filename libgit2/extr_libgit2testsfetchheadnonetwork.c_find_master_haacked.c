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
typedef  void git_oid ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_UNUSED (void*) ; 
 int /*<<< orphan*/  cl_assert (unsigned int) ; 
 int find_master_haacked_called ; 
 int found_haacked ; 
 int found_master ; 
 int /*<<< orphan*/  strcmp (char*,char const*) ; 

int find_master_haacked(const char *ref_name, const char *remote_url, const git_oid *oid, unsigned int is_merge, void *payload)
{
	GIT_UNUSED(remote_url);
	GIT_UNUSED(oid);
	GIT_UNUSED(payload);

	find_master_haacked_called = true;

	if (!strcmp("refs/heads/master", ref_name)) {
		cl_assert(is_merge);
		found_master = true;
	}
	if (!strcmp("refs/heads/haacked", ref_name)) {
		cl_assert(is_merge);
		found_haacked = true;
	}

	return 0;
}