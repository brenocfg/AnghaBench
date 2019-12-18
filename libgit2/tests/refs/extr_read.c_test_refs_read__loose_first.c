#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ git_reference ;

/* Variables and functions */
 int GIT_REFERENCE_DIRECT ; 
 int /*<<< orphan*/  cl_assert (int) ; 
 int /*<<< orphan*/  cl_assert_equal_s (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_reference_free (TYPE_1__*) ; 
 int /*<<< orphan*/  git_reference_lookup (TYPE_1__**,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int git_reference_type (TYPE_1__*) ; 
 int /*<<< orphan*/  packed_head_name ; 
 int /*<<< orphan*/  packed_test_head_name ; 
 scalar_t__ reference_is_packed (TYPE_1__*) ; 

void test_refs_read__loose_first(void)
{
	/* assure that a loose reference is looked up before a packed reference */
	git_reference *reference;

	cl_git_pass(git_reference_lookup(&reference, g_repo, packed_head_name));
	git_reference_free(reference);
	cl_git_pass(git_reference_lookup(&reference, g_repo, packed_test_head_name));
	cl_assert(git_reference_type(reference) & GIT_REFERENCE_DIRECT);
	cl_assert(reference_is_packed(reference) == 0);
	cl_assert_equal_s(reference->name, packed_test_head_name);

	git_reference_free(reference);
}