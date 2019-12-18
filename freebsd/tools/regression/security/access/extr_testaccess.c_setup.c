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
struct TYPE_2__ {int /*<<< orphan*/  fd_group; int /*<<< orphan*/  fd_owner; int /*<<< orphan*/  fd_name; int /*<<< orphan*/  fd_mode; } ;

/* Variables and functions */
 int O_CREAT ; 
 int O_EXCL ; 
 int chown (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  close (int) ; 
 TYPE_1__* fd_list ; 
 int fd_list_count ; 
 int open (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  perror (char*) ; 

int
setup(void)
{
	int i, error;

	for (i = 0; i < fd_list_count; i++) {
		error = open(fd_list[i].fd_name, O_CREAT | O_EXCL, fd_list[i].fd_mode);
		if (error == -1) {
			perror("open");
			return (error);
		}
		close(error);
		error = chown(fd_list[i].fd_name, fd_list[i].fd_owner,
		    fd_list[i].fd_group);
		if (error) {
			perror("chown");
			return (error);
		}
	}
	return (0);
}