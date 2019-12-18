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
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  STDERR_FILENO ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  err (int,char*,...) ; 
 int open (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int read (int,char*,int) ; 
 int write (int /*<<< orphan*/ ,char*,int) ; 

void
cat(char *file)
{
	register int fd, nr, nw;
	char buf[1024];

	if ((fd = open(file, O_RDONLY, 0)) < 0)
		err(1, "%s", file);

	while ((nr = read(fd, buf, sizeof(buf))) > 0)
		if ((nw = write(STDERR_FILENO, buf, nr)) == -1)
			err(1, "write to stderr");
	if (nr != 0)
		err(1, "%s", file);
	(void)close(fd);
}