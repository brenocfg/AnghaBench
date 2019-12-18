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
struct stat {size_t st_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  err (int,char*,char*) ; 
 int fstat (int,struct stat*) ; 
 int open (char*,int /*<<< orphan*/ ) ; 

int
opensize(char *name, size_t *size)
{
	struct stat s;
	int fd = open(name, O_RDONLY);
	if (fd < 0) {
		err(1, "cannot open \"%s\"", name);
	}
	if (fstat(fd, &s) == -1) {
		err(1, "cannot stat \"%s\"", name);
	}
	*size = s.st_size;
	return fd;
}