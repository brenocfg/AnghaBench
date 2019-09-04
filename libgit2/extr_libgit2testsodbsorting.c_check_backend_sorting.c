#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_odb_backend ;
typedef  int /*<<< orphan*/  git_odb ;
struct TYPE_2__ {int /*<<< orphan*/  position; } ;
typedef  TYPE_1__ fake_backend ;

/* Variables and functions */
 int /*<<< orphan*/  cl_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_assert_equal_sz (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_odb_get_backend (int /*<<< orphan*/ **,int /*<<< orphan*/ *,size_t) ; 
 size_t git_odb_num_backends (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void check_backend_sorting(git_odb *odb)
{
	size_t i, max_i = git_odb_num_backends(odb);
	fake_backend *internal;

	for (i = 0; i < max_i; ++i) {
		cl_git_pass(git_odb_get_backend((git_odb_backend **)&internal, odb, i));
		cl_assert(internal != NULL);
		cl_assert_equal_sz(i, internal->position);
	}
}