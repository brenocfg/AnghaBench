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
struct winch {int fd; int /*<<< orphan*/  work; int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int /*<<< orphan*/  __free_winch (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  os_close_file (int) ; 

__attribute__((used)) static void free_winch(struct winch *winch)
{
	int fd = winch->fd;
	winch->fd = -1;
	if (fd != -1)
		os_close_file(fd);
	list_del(&winch->list);
	__free_winch(&winch->work);
}