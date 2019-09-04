#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  offset; int /*<<< orphan*/  time; } ;
struct TYPE_6__ {TYPE_1__ when; int /*<<< orphan*/  email; int /*<<< orphan*/  name; } ;
typedef  TYPE_2__ git_signature ;

/* Variables and functions */
 int /*<<< orphan*/  cl_assert_equal_i (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_assert_equal_s (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_signature_free (TYPE_2__*) ; 
 int /*<<< orphan*/  git_signature_from_buffer (TYPE_2__**,char*) ; 

void test_commit_signature__from_buf(void)
{
	git_signature *sign;

	cl_git_pass(git_signature_from_buffer(&sign, "Test User <test@test.tt> 1461698487 +0200"));
	cl_assert_equal_s("Test User", sign->name);
	cl_assert_equal_s("test@test.tt", sign->email);
	cl_assert_equal_i(1461698487, sign->when.time);
	cl_assert_equal_i(120, sign->when.offset);
	git_signature_free(sign);
}