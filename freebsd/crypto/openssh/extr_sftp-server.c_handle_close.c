#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  name; int /*<<< orphan*/  dirp; int /*<<< orphan*/  fd; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOENT ; 
 int /*<<< orphan*/  HANDLE_DIR ; 
 int /*<<< orphan*/  HANDLE_FILE ; 
 int close (int /*<<< orphan*/ ) ; 
 int closedir (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 scalar_t__ handle_is_ok (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  handle_unused (int) ; 
 TYPE_1__* handles ; 

__attribute__((used)) static int
handle_close(int handle)
{
	int ret = -1;

	if (handle_is_ok(handle, HANDLE_FILE)) {
		ret = close(handles[handle].fd);
		free(handles[handle].name);
		handle_unused(handle);
	} else if (handle_is_ok(handle, HANDLE_DIR)) {
		ret = closedir(handles[handle].dirp);
		free(handles[handle].name);
		handle_unused(handle);
	} else {
		errno = ENOENT;
	}
	return ret;
}