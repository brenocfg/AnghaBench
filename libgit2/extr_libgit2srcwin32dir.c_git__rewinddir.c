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
typedef  int /*<<< orphan*/  git_win32_path ;
struct TYPE_3__ {int first; int /*<<< orphan*/  dir; int /*<<< orphan*/  h; int /*<<< orphan*/  f; } ;
typedef  TYPE_1__ git__DIR ;

/* Variables and functions */
 int /*<<< orphan*/  FindClose (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FindFirstFileW (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GIT_ERROR_OS ; 
 int /*<<< orphan*/  INVALID_HANDLE_VALUE ; 
 int /*<<< orphan*/  git_error_set (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_win32__findfirstfile_filter (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void git__rewinddir(git__DIR *d)
{
	git_win32_path filter_w;

	if (!d)
		return;

	if (d->h != INVALID_HANDLE_VALUE) {
		FindClose(d->h);
		d->h = INVALID_HANDLE_VALUE;
		d->first = 0;
	}

	if (!git_win32__findfirstfile_filter(filter_w, d->dir))
		return;

	d->h = FindFirstFileW(filter_w, &d->f);

	if (d->h == INVALID_HANDLE_VALUE)
		git_error_set(GIT_ERROR_OS, "could not open directory '%s'", d->dir);
	else
		d->first = 1;
}