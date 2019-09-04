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
typedef  int /*<<< orphan*/  git_signature ;

/* Variables and functions */
 int /*<<< orphan*/  cl_assert (int) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_signature__equal (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_signature_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_signature_from_buffer (int /*<<< orphan*/ **,char*) ; 

void test_commit_signature__pos_and_neg_zero_offsets_dont_match(void)
{
	git_signature *with_neg_zero;
	git_signature *with_pos_zero;

	cl_git_pass(git_signature_from_buffer(&with_neg_zero, "Test User <test@test.tt> 1461698487 -0000"));
	cl_git_pass(git_signature_from_buffer(&with_pos_zero, "Test User <test@test.tt> 1461698487 +0000"));

	cl_assert(!git_signature__equal(with_neg_zero, with_pos_zero));

	git_signature_free((git_signature *)with_neg_zero);
	git_signature_free((git_signature *)with_pos_zero);
}