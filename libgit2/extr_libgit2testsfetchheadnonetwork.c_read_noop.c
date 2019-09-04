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

__attribute__((used)) static int read_noop(const char *ref_name, const char *remote_url,
	const git_oid *oid, unsigned int is_merge, void *payload)
{
	GIT_UNUSED(ref_name);
	GIT_UNUSED(remote_url);
	GIT_UNUSED(oid);
	GIT_UNUSED(is_merge);
	GIT_UNUSED(payload);

	return 0;
}