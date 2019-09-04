#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_5__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ git_error_state ;
struct TYPE_7__ {int /*<<< orphan*/  message; int /*<<< orphan*/  klass; } ;

/* Variables and functions */
 int /*<<< orphan*/  cl_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_assert_equal_i (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_assert_equal_s (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_error_clear () ; 
 TYPE_5__* git_error_last () ; 
 int /*<<< orphan*/  git_error_set (int,char*,char*) ; 
 int /*<<< orphan*/  git_error_state_capture (TYPE_1__*,int) ; 
 int /*<<< orphan*/  git_error_state_free (TYPE_1__*) ; 
 int /*<<< orphan*/  git_error_state_restore (TYPE_1__*) ; 

void test_core_errors__free_state(void)
{
	git_error_state err_state = {0};

	git_error_clear();

	git_error_set(42, "Foo: %s", "bar");
	cl_assert_equal_i(-1, git_error_state_capture(&err_state, -1));

	git_error_set(99, "Bar: %s", "foo");

	git_error_state_free(&err_state);

	cl_assert_equal_i(99, git_error_last()->klass);
	cl_assert_equal_s("Bar: foo", git_error_last()->message);

	git_error_state_restore(&err_state);

	cl_assert(git_error_last() == NULL);
}