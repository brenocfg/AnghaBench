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
 int MAXPATHLEN ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  _PATH_DEVZERO ; 
 int /*<<< orphan*/  abort () ; 
 size_t atoi (char*) ; 
 int open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int read (int,char*,size_t) ; 

int
main(int argc, char *argv[])
{
	char b[MAXPATHLEN];
	int fd, n;
	size_t len = atoi(argv[1]);

	if ((fd = open(_PATH_DEVZERO, O_RDONLY)) == -1)
		abort();
	if ((n = read(fd, b, len)) == -1)
		abort();
	(void)printf("%s\n", b);
	return (0);
}