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
typedef  int /*<<< orphan*/  git_filebuf ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_FILEBUF_INIT ; 
 int /*<<< orphan*/  TEST_CONFIG ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_filebuf_commit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_filebuf_open (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  git_filebuf_printf (int /*<<< orphan*/ *,char*) ; 

void test_config_stress__initialize(void)
{
	git_filebuf file = GIT_FILEBUF_INIT;

	cl_git_pass(git_filebuf_open(&file, TEST_CONFIG, 0, 0666));

	git_filebuf_printf(&file, "[color]\n\tui = auto\n");
	git_filebuf_printf(&file, "[core]\n\teditor = \n");

	cl_git_pass(git_filebuf_commit(&file));
}