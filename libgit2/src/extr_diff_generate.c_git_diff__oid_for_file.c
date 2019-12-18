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
typedef  scalar_t__ uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
typedef  int /*<<< orphan*/  git_oid ;
typedef  scalar_t__ git_off_t ;
struct TYPE_4__ {char* path; scalar_t__ file_size; int /*<<< orphan*/  mode; } ;
typedef  TYPE_1__ git_index_entry ;
typedef  int /*<<< orphan*/  git_diff ;
typedef  int /*<<< orphan*/  entry ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_ERROR_NOMEMORY ; 
 scalar_t__ UINT32_MAX ; 
 int git_diff__oid_for_entry (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_error_set (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

int git_diff__oid_for_file(
	git_oid *out,
	git_diff *diff,
	const char *path,
	uint16_t mode,
	git_off_t size)
{
	git_index_entry entry;

	if (size < 0 || size > UINT32_MAX) {
		git_error_set(GIT_ERROR_NOMEMORY, "file size overflow (for 32-bits) on '%s'", path);
		return -1;
	}

	memset(&entry, 0, sizeof(entry));
	entry.mode = mode;
	entry.file_size = (uint32_t)size;
	entry.path = (char *)path;

	return git_diff__oid_for_entry(out, diff, &entry, mode, NULL);
}