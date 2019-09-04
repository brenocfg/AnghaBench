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
 int /*<<< orphan*/  GIT_OBJECT_DIR_MODE ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  odb_dir ; 
 int /*<<< orphan*/  p_mkdir (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void make_odb_dir(void)
{
	cl_git_pass(p_mkdir(odb_dir, GIT_OBJECT_DIR_MODE));
}