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
 int /*<<< orphan*/  cl_fail (char*) ; 

int update_tips_fail_on_call(const char *ref, const git_oid *old, const git_oid *new, void *data)
{
	GIT_UNUSED(ref);
	GIT_UNUSED(old);
	GIT_UNUSED(new);
	GIT_UNUSED(data);

	cl_fail("update tips called");
	return 0;
}