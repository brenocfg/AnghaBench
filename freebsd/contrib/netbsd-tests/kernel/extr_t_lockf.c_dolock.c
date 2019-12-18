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
typedef  int off_t ;

/* Variables and functions */
 int /*<<< orphan*/  ATF_REQUIRE_MSG (int,char*) ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int errno ; 
 int lockf (int,int,int) ; 
 int lseek (int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
dolock(int fd, int op, off_t lk_off, off_t lk_size)
{
	off_t result;
	int ret;

	result = lseek(fd, lk_off, SEEK_SET);
	if (result == -1) {
		return errno;
	}
	ATF_REQUIRE_MSG(result == lk_off, "lseek to wrong offset");
	ret = lockf(fd, op, lk_size);
	if (ret == -1) {
		return errno;
	}
	return 0;
}