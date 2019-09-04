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
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  git__on_shutdown (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git__pack_cache ; 
 int /*<<< orphan*/  git_mwindow_files_free ; 
 int git_strmap_new (int /*<<< orphan*/ *) ; 

int git_mwindow_global_init(void)
{
	assert(!git__pack_cache);

	git__on_shutdown(git_mwindow_files_free);
	return git_strmap_new(&git__pack_cache);
}