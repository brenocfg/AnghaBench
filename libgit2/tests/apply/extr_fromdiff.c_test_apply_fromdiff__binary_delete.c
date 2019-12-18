#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  size; int /*<<< orphan*/  ptr; } ;
typedef  TYPE_1__ git_buf ;

/* Variables and functions */
 int /*<<< orphan*/  FILE_BINARY_DELTA_MODIFIED ; 
 int /*<<< orphan*/  FILE_BINARY_DELTA_MODIFIED_LEN ; 
 TYPE_1__ GIT_BUF_INIT ; 
 int /*<<< orphan*/  apply_gitbuf (TYPE_1__*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  binary_opts ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 

void test_apply_fromdiff__binary_delete(void)
{
	git_buf original = GIT_BUF_INIT;

	original.ptr = FILE_BINARY_DELTA_MODIFIED;
	original.size = FILE_BINARY_DELTA_MODIFIED_LEN;

	cl_git_pass(apply_gitbuf(
		&original, "binary.bin",
		NULL, NULL,
		NULL, &binary_opts));
}