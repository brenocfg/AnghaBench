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
struct TYPE_3__ {int /*<<< orphan*/ * fmh; int /*<<< orphan*/ * data; } ;
typedef  TYPE_1__ git_map ;

/* Variables and functions */
 int /*<<< orphan*/  CloseHandle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GIT_ERROR_OS ; 
 int /*<<< orphan*/  UnmapViewOfFile (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_error_set (int /*<<< orphan*/ ,char*) ; 

int p_munmap(git_map *map)
{
	int error = 0;

	assert(map != NULL);

	if (map->data) {
		if (!UnmapViewOfFile(map->data)) {
			git_error_set(GIT_ERROR_OS, "failed to munmap. Could not unmap view of file");
			error = -1;
		}
		map->data = NULL;
	}

	if (map->fmh) {
		if (!CloseHandle(map->fmh)) {
			git_error_set(GIT_ERROR_OS, "failed to munmap. Could not close handle");
			error = -1;
		}
		map->fmh = NULL;
	}

	return error;
}