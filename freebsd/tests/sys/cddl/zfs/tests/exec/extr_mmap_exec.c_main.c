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
struct stat {int /*<<< orphan*/  st_size; } ;

/* Variables and functions */
 scalar_t__ MAP_FAILED ; 
 int /*<<< orphan*/  MAP_SHARED ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  PROT_EXEC ; 
 int errno ; 
 scalar_t__ fstat (int,struct stat*) ; 
 scalar_t__ mmap (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int open (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

int
main(int argc, char *argv[])
{
	int fd;
	struct stat statbuf;

	if (argc != 2) {
		(void) printf("Error: missing binary name.\n");
		(void) printf("Usage:\n\t%s <binary name>\n",
		    argv[0]);
		return (1);
	}

	errno = 0;

	if ((fd = open(argv[1], O_RDONLY)) < 0) {
		perror("open");
		return (errno);
	}
	if (fstat(fd, &statbuf) < 0) {
		perror("fstat");
		return (errno);
	}

	if (mmap(0, statbuf.st_size,
	    PROT_EXEC, MAP_SHARED, fd, 0) == MAP_FAILED) {
		perror("mmap");
		return (errno);
	}

	return (0);
}