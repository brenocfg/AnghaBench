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

/* Variables and functions */
 size_t ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cl_fixture_cleanup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  destpath ; 
 int /*<<< orphan*/  filepath ; 
 int /*<<< orphan*/  git_buf_dispose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * paths ; 

void test_odb_alternates__cleanup(void)
{
	size_t i;

	git_buf_dispose(&destpath);
	git_buf_dispose(&filepath);

	for (i = 0; i < ARRAY_SIZE(paths); i++)
		cl_fixture_cleanup(paths[i]);
}