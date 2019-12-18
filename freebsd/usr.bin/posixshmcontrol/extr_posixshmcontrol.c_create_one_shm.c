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
 int /*<<< orphan*/  close (int) ; 
 int shm_open (char const*,int,long) ; 
 int /*<<< orphan*/  warn (char*,char const*) ; 

__attribute__((used)) static int
create_one_shm(const char *path, long mode)
{
	int fd;

	fd = shm_open(path, O_RDWR | O_CREAT, mode);
	if (fd == -1) {
		warn("create %s", path);
		return (1);
	}
	close(fd);
	return (0);
}