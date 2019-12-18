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
 int gcov_ctors_done ; 
 int /*<<< orphan*/  gcov_fs_init () ; 
 int /*<<< orphan*/  gcov_invoke_lf_ctors ; 
 int /*<<< orphan*/  linker_file_foreach (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
gcov_invoke_ctors(void)
{

	gcov_fs_init();

	linker_file_foreach(gcov_invoke_lf_ctors, NULL);
	gcov_ctors_done = 1;
}