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
 int O_CREAT ; 
 int O_RDWR ; 
 int O_TRUNC ; 
 int /*<<< orphan*/  close (int) ; 
 int count ; 
 int /*<<< orphan*/  do_trunc (int) ; 
 int /*<<< orphan*/  do_write (int) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  filename ; 
 int open (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  parse_options (int,char**) ; 
 int /*<<< orphan*/  perror (char*) ; 

int
main(int argc, char *argv[])
{
	int i = 0;
	int fd = -1;

	parse_options(argc, argv);

	fd = open(filename, O_RDWR|O_CREAT|O_TRUNC, 0666);
	if (fd < 0) {
		perror("open");
		exit(3);
	}

	while (i < count) {
		(void) do_write(fd);
		(void) do_trunc(fd);

		i++;
	}

	(void) close(fd);
	return (0);
}