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
typedef  int /*<<< orphan*/  fd_set ;

/* Variables and functions */
 scalar_t__ EAGAIN ; 
 int /*<<< orphan*/  FD_SET (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FD_ZERO (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  err (int,char*) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  errx (int,char*,int) ; 
 int /*<<< orphan*/  exit (int) ; 
 int select (int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  warn (char*) ; 
 int write (int,char*,unsigned long) ; 

__attribute__((used)) static void
write_frame(int fd, char *buf, unsigned long buflen)
{
	fd_set wfd;
	int i;

	while (buflen) {
		FD_ZERO(&wfd);
		FD_SET(fd, &wfd);
		i = select(fd+1, NULL, &wfd, NULL, NULL);
		if (i < 0)
			err(1, "select failed");
		if (i != 1) {
			errx(1, "select returned unexpected value %d\n", i);
			exit(1);
		}
		i = write(fd, buf, buflen);
		if (i < 0) {
			if (errno != EAGAIN)
				warn("write failed");
			exit(1);
		}
		buf += i;
		buflen -= i;
	}
}