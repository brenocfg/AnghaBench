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
 int /*<<< orphan*/  O_RDWR ; 
 int /*<<< orphan*/  SESIOC_INIT ; 
 int /*<<< orphan*/  close (int) ; 
 scalar_t__ ioctl (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int open (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  perror (char*) ; 

int
main(int a, char **v)
{
	int fd;

	while (*++v) {
		fd = open(*v, O_RDWR);
		if (fd < 0) {
			perror(*v);
			continue;
		}
		if (ioctl(fd, SESIOC_INIT, NULL) < 0) {
			perror("SESIOC_GETNOBJ");
		}
		(void) close(fd);
	}
	return (0);
}