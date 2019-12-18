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
typedef  scalar_t__ ssize_t ;

/* Variables and functions */
 int BLOCKSIZE ; 
 int /*<<< orphan*/  BLOCKS_FILENAME ; 
 scalar_t__ ENOSPC ; 
 int NUMTRIES ; 
 int O_CREAT ; 
 int O_RDWR ; 
 int O_TRUNC ; 
 int /*<<< orphan*/  bzero (char*,int) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  err (int,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  exit (int) ; 
 int open (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  unlink (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  warn (char*) ; 
 int /*<<< orphan*/  warnx (char*,int,scalar_t__) ; 
 scalar_t__ write (int,char*,int) ; 

__attribute__((used)) static void
fill_blocks(void)
{
	char block[BLOCKSIZE];
	ssize_t len;
	int fd, i;

	fd = open(BLOCKS_FILENAME, O_CREAT | O_TRUNC | O_RDWR, 0600);
	if (fd < 0)
		err(-1, "fill_blocks: open(%s)", BLOCKS_FILENAME);

	/*
	 * First step: fill the disk device.  Keep extending the file until
	 * we hit our first error, and hope it is ENOSPC.
	 */
	bzero(block, BLOCKSIZE);
	errno = 0;
	while (1) {
		len = write(fd, block, BLOCKSIZE);
		if (len < 0)
			break;
		if (len != BLOCKSIZE) {
			warnx("fill_blocks: write(%d) returned %zd",
			    BLOCKSIZE, len);
			close(fd);
			(void)unlink(BLOCKS_FILENAME);
			exit(-1);
		}

	}
	if (errno != ENOSPC) {
		warn("fill_blocks: write");
		close(fd);
		(void)unlink(BLOCKS_FILENAME);
		exit(-1);
	}

	/*
	 * Second step: generate NUMTRIES instances of the error by retrying
	 * the write.
	 */
	for (i = 0; i < NUMTRIES; i++) {
		len = write(fd, block, BLOCKSIZE);
		if (len < 0 && errno != ENOSPC) {
			warn("fill_blocks: write after ENOSPC");
			close(fd);
			(void)unlink(BLOCKS_FILENAME);
			exit(-1);
		}
	}

	close(fd);
	(void)unlink(BLOCKS_FILENAME);
}