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
struct checkout_cancel_at {int error; int /*<<< orphan*/  filename; int /*<<< orphan*/  count; } ;
typedef  int /*<<< orphan*/  git_diff_file ;
typedef  int /*<<< orphan*/  const* git_checkout_notify_t ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_UNUSED (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  strcmp (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int checkout_cancel_cb(
	git_checkout_notify_t why,
	const char *path,
	const git_diff_file *b,
	const git_diff_file *t,
	const git_diff_file *w,
	void *payload)
{
	struct checkout_cancel_at *ca = payload;

	GIT_UNUSED(why); GIT_UNUSED(b); GIT_UNUSED(t); GIT_UNUSED(w);

	ca->count++;

	if (!strcmp(path, ca->filename))
		return ca->error;

	return 0;
}