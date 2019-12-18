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
struct tube {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct tube*) ; 
 int /*<<< orphan*/  tube_close_read (struct tube*) ; 
 int /*<<< orphan*/  tube_close_write (struct tube*) ; 
 int /*<<< orphan*/  tube_remove_bg_listen (struct tube*) ; 
 int /*<<< orphan*/  tube_remove_bg_write (struct tube*) ; 

void tube_delete(struct tube* tube)
{
	if(!tube) return;
	tube_remove_bg_listen(tube);
	tube_remove_bg_write(tube);
	/* close fds after deleting commpoints, to be sure.
	 *            Also epoll does not like closing fd before event_del */
	tube_close_read(tube);
	tube_close_write(tube);
	free(tube);
}