#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  real_email; int /*<<< orphan*/  real_name; int /*<<< orphan*/  replace_email; int /*<<< orphan*/  replace_name; } ;
typedef  TYPE_1__ mailmap_entry ;
typedef  int /*<<< orphan*/  git_mailmap ;

/* Variables and functions */
 int /*<<< orphan*/  cl_assert_equal_s (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_mailmap_resolve (char const**,char const**,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void check_mailmap_resolve(
	const git_mailmap *mailmap, const mailmap_entry *resolved, size_t resolved_size)
{
	const char *resolved_name = NULL;
	const char *resolved_email = NULL;
	size_t idx;

	/* Check that the resolver behaves correctly */
	for (idx = 0; idx < resolved_size; ++idx) {
		cl_git_pass(git_mailmap_resolve(
			&resolved_name, &resolved_email, mailmap,
			resolved[idx].replace_name, resolved[idx].replace_email));
		cl_assert_equal_s(resolved_name, resolved[idx].real_name);
		cl_assert_equal_s(resolved_email, resolved[idx].real_email);
	}
}