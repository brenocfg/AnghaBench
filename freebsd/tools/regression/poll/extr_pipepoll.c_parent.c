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
 int /*<<< orphan*/  FIFONAME ; 
 scalar_t__ FT_FIFO ; 
 int O_NONBLOCK ; 
 int O_WRONLY ; 
 int /*<<< orphan*/  SIGUSR1 ; 
 scalar_t__ close (int) ; 
 int /*<<< orphan*/  cpid ; 
 int /*<<< orphan*/  err (int,char*) ; 
 scalar_t__ filetype ; 
 int /*<<< orphan*/  kill (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int open (int /*<<< orphan*/ ,int) ; 
 int state ; 
 int /*<<< orphan*/  usleep (int) ; 
 int write (int,char*,int) ; 

__attribute__((used)) static void
parent(int fd)
{
	usleep(1);
	while (state != 1)
		;
	if (filetype == FT_FIFO) {
		fd = open(FIFONAME, O_WRONLY | O_NONBLOCK);
		if (fd < 0)
			err(1, "open for write");
	}
	kill(cpid, SIGUSR1);

	usleep(1);
	while (state != 2)
		;
	if (write(fd, "", 1) != 1)
		err(1, "write");
	kill(cpid, SIGUSR1);

	usleep(1);
	while (state != 3)
		;
	if (close(fd) != 0)
		err(1, "close for write");
	kill(cpid, SIGUSR1);

	usleep(1);
	while (state != 4)
		;
	if (filetype != FT_FIFO)
		return;
	fd = open(FIFONAME, O_WRONLY | O_NONBLOCK);
	if (fd < 0)
		err(1, "open for write");
	kill(cpid, SIGUSR1);

	usleep(1);
	while (state != 5)
		;
	if (write(fd, "", 1) != 1)
		err(1, "write");
	kill(cpid, SIGUSR1);

	usleep(1);
	while (state != 6)
		;
	if (close(fd) != 0)
		err(1, "close for write");
	kill(cpid, SIGUSR1);

	usleep(1);
	while (state != 7)
		;
}