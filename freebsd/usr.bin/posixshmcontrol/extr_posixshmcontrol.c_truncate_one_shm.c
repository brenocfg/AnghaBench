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
typedef  int /*<<< orphan*/  uint64_t ;

/* Variables and functions */
 int /*<<< orphan*/  O_RDWR ; 
 int /*<<< orphan*/  close (int) ; 
 int ftruncate (int,int /*<<< orphan*/ ) ; 
 int shm_open (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  warn (char*,char const*) ; 

__attribute__((used)) static int
truncate_one_shm(const char *path, uint64_t newsize)
{
	int error, fd, ret;

	ret = 0;
	fd = shm_open(path, O_RDWR, 0);
	if (fd == -1) {
		warn("open %s", path);
		return (1);
	}
	error = ftruncate(fd, newsize);
	if (error == -1) {
		warn("truncate %s", path);
		ret = 1;
	}
	close(fd);
	return (ret);
}