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
struct update_submodule_cb_payload {int update_tips_called; } ;
typedef  char git_oid ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_UNUSED (char const*) ; 

__attribute__((used)) static int update_tips(const char *refname, const git_oid *a, const git_oid *b, void *data)
{
	struct update_submodule_cb_payload *update_payload = data;

	GIT_UNUSED(refname);
	GIT_UNUSED(a);
	GIT_UNUSED(b);

	update_payload->update_tips_called = 1;

	return 1;
}