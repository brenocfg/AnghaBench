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

/* Variables and functions */
 scalar_t__ EACCES ; 
 scalar_t__ ENXIO ; 
 int EXIT_FAILURE ; 
 int EXIT_SUCCESS ; 
 int /*<<< orphan*/  O_RDWR ; 
 int /*<<< orphan*/  close (int) ; 
 scalar_t__ errno ; 
 int open (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*) ; 

int
main(void)
{
	int exitcode, fd;

	fd = open("/dev/puffs", O_RDWR);
	if (fd != -1) {
		printf("yes\n");
		close(fd);
		exitcode = EXIT_SUCCESS;
	} else {
		if (errno == ENXIO) {
			printf("enxio\n");
			exitcode = EXIT_SUCCESS;
		} else if (errno == EACCES) {
			printf("eacces\n");
			exitcode = EXIT_SUCCESS;
		} else {
			printf("failed\n");
			exitcode = EXIT_FAILURE;
		}
	}

	return exitcode;
}