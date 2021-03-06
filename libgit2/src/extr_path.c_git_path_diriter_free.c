#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  path; int /*<<< orphan*/  ic; int /*<<< orphan*/ * dir; } ;
typedef  TYPE_1__ git_path_diriter ;

/* Variables and functions */
 int /*<<< orphan*/  closedir (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_buf_dispose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_path_iconv_clear (int /*<<< orphan*/ *) ; 

void git_path_diriter_free(git_path_diriter *diriter)
{
	if (diriter == NULL)
		return;

	if (diriter->dir) {
		closedir(diriter->dir);
		diriter->dir = NULL;
	}

#ifdef GIT_USE_ICONV
	git_path_iconv_clear(&diriter->ic);
#endif

	git_buf_dispose(&diriter->path);
}