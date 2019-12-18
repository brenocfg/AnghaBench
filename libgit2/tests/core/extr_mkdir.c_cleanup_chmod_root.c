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
typedef  int /*<<< orphan*/  mode_t ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_RMDIR_EMPTY_HIERARCHY ; 
 int /*<<< orphan*/  git__free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_futils_rmdir_r (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  p_umask (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cleanup_chmod_root(void *ref)
{
	mode_t *mode = ref;

	if (mode != NULL) {
		(void)p_umask(*mode);
		git__free(mode);
	}

	git_futils_rmdir_r("r", NULL, GIT_RMDIR_EMPTY_HIERARCHY);
}