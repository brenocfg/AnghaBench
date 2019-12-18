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
 int /*<<< orphan*/  EINTR ; 
 int /*<<< orphan*/  errno ; 
 int write (int,char*,int) ; 

__attribute__((used)) static int
sppd_write(int fd, char *buffer, int size)
{
	int	n, wrote;

	for (wrote = 0; size > 0; ) {
		n = write(fd, buffer, size);
		switch (n) {
		case -1:
			if (errno != EINTR)
				return (-1);
			break;

		case 0: 
			/* XXX can happen? */
			break;

		default:
			wrote += n;
			buffer += n;
			size -= n;
			break;
		}
	}

	return (wrote);
}