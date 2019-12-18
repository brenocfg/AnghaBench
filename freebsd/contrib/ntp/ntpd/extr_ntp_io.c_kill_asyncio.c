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
struct TYPE_2__ {int /*<<< orphan*/  fd; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLOCKIO () ; 
 int /*<<< orphan*/  UNBLOCKIO () ; 
 int /*<<< orphan*/  close_and_delete_fd_from_list (int /*<<< orphan*/ ) ; 
 TYPE_1__* fd_list ; 
 scalar_t__ maxactivefd ; 

void
kill_asyncio(
	int	startfd
	)
{
	BLOCKIO();

	/*
	 * In the child process we do not maintain activefds and
	 * maxactivefd.  Zeroing maxactivefd disables code which
	 * maintains it in close_and_delete_fd_from_list().
	 */
	maxactivefd = 0;

	while (fd_list != NULL)
		close_and_delete_fd_from_list(fd_list->fd);

	UNBLOCKIO();
}