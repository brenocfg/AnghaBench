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
struct TYPE_4__ {int next_unused; int use; int fd; int flags; scalar_t__ bytes_write; scalar_t__ bytes_read; int /*<<< orphan*/  name; int /*<<< orphan*/ * dirp; } ;
typedef  int /*<<< orphan*/  Handle ;
typedef  int /*<<< orphan*/  DIR ;

/* Variables and functions */
 int first_unused_handle ; 
 int /*<<< orphan*/  handle_unused (scalar_t__) ; 
 TYPE_1__* handles ; 
 scalar_t__ num_handles ; 
 TYPE_1__* xreallocarray (TYPE_1__*,scalar_t__,int) ; 
 int /*<<< orphan*/  xstrdup (char const*) ; 

__attribute__((used)) static int
handle_new(int use, const char *name, int fd, int flags, DIR *dirp)
{
	int i;

	if (first_unused_handle == -1) {
		if (num_handles + 1 <= num_handles)
			return -1;
		num_handles++;
		handles = xreallocarray(handles, num_handles, sizeof(Handle));
		handle_unused(num_handles - 1);
	}

	i = first_unused_handle;
	first_unused_handle = handles[i].next_unused;

	handles[i].use = use;
	handles[i].dirp = dirp;
	handles[i].fd = fd;
	handles[i].flags = flags;
	handles[i].name = xstrdup(name);
	handles[i].bytes_read = handles[i].bytes_write = 0;

	return i;
}