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
typedef  int /*<<< orphan*/  git_diff_file ;
typedef  int /*<<< orphan*/  const* git_checkout_notify_t ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_UNUSED (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  strcmp (char const*,char const*) ; 

__attribute__((used)) static int clone_cancel_checkout_cb(
	git_checkout_notify_t why,
	const char *path,
	const git_diff_file *b,
	const git_diff_file *t,
	const git_diff_file *w,
	void *payload)
{
	const char *at_file = payload;
	GIT_UNUSED(why); GIT_UNUSED(b); GIT_UNUSED(t); GIT_UNUSED(w);
	if (!strcmp(path, at_file))
		return -12345;
	return 0;
}