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
typedef  size_t ssize_t ;

/* Variables and functions */
 int EIO ; 
 int* disk_fd ; 
 int disk_index ; 
 int errno ; 
 size_t pread (int,void*,size_t,int /*<<< orphan*/ ) ; 

int
test_diskread(void *arg, int unit, uint64_t offset, void *dst, size_t size,
    size_t *resid_return)
{
	ssize_t n;

	if (unit > disk_index || disk_fd[unit] == -1)
		return (EIO);
	n = pread(disk_fd[unit], dst, size, offset);
	if (n < 0)
		return (errno);
	*resid_return = size - n;
	return (0);
}