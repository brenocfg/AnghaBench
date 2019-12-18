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
typedef  int /*<<< orphan*/  off_t ;
struct TYPE_3__ {int /*<<< orphan*/  src_fd; } ;
typedef  TYPE_1__ file_pair ;

/* Variables and functions */
 size_t IO_BUFFER_SIZE ; 
 int /*<<< orphan*/  SEEK_CUR ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  lseek (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

extern void
io_fix_src_pos(file_pair *pair, size_t rewind_size)
{
	assert(rewind_size <= IO_BUFFER_SIZE);

	if (rewind_size > 0) {
		// This doesn't need to work on unseekable file descriptors,
		// so just ignore possible errors.
		(void)lseek(pair->src_fd, -(off_t)(rewind_size), SEEK_CUR);
	}

	return;
}