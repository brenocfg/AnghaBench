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
typedef  int /*<<< orphan*/  git_reference ;
typedef  int /*<<< orphan*/  git_buf ;

/* Variables and functions */
 scalar_t__ GIT_REFERENCE_SYMBOLIC ; 
 scalar_t__ git_buf_oom (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_buf_puts (int /*<<< orphan*/ *,char const*) ; 
 char const* git_oid_tostr_s (int /*<<< orphan*/ ) ; 
 scalar_t__ git_reference__is_branch (char const*) ; 
 scalar_t__ git_reference__is_remote (char const*) ; 
 scalar_t__ git_reference__is_tag (char const*) ; 
 char const* git_reference__shorthand (char const*) ; 
 char const* git_reference_symbolic_target (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_reference_target (int /*<<< orphan*/ *) ; 
 scalar_t__ git_reference_type (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int checkout_message(git_buf *out, git_reference *old, const char *new)
{
	git_buf_puts(out, "checkout: moving from ");

	if (git_reference_type(old) == GIT_REFERENCE_SYMBOLIC)
		git_buf_puts(out, git_reference__shorthand(git_reference_symbolic_target(old)));
	else
		git_buf_puts(out, git_oid_tostr_s(git_reference_target(old)));

	git_buf_puts(out, " to ");

	if (git_reference__is_branch(new) ||
		git_reference__is_tag(new) ||
		git_reference__is_remote(new))
		git_buf_puts(out, git_reference__shorthand(new));
	else
		git_buf_puts(out, new);

	if (git_buf_oom(out))
		return -1;

	return 0;
}