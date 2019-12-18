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
struct stat {scalar_t__ st_size; } ;

/* Variables and functions */
 scalar_t__ BBSIZE ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  bootarea ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  err (int,char*,char*) ; 
 int /*<<< orphan*/  errx (int,char*,char*) ; 
 int /*<<< orphan*/  fstat (int,struct stat*) ; 
 int open (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ read (int,int /*<<< orphan*/ ,scalar_t__) ; 
 char* xxboot ; 

__attribute__((used)) static void
readboot(void)
{
	int fd;
	struct stat st;

	if (xxboot == NULL)
		xxboot = "/boot/boot";
	fd = open(xxboot, O_RDONLY);
	if (fd < 0)
		err(1, "cannot open %s", xxboot);
	fstat(fd, &st);
	if (st.st_size <= BBSIZE) {
		if (read(fd, bootarea, st.st_size) != st.st_size)
			err(1, "read error %s", xxboot);
		close(fd);
		return;
	}
	errx(1, "boot code %s is wrong size", xxboot);
}