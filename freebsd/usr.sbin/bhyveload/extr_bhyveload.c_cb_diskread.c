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
 int /*<<< orphan*/ * disk_fd ; 
 int errno ; 
 int ndisks ; 
 size_t pread (int /*<<< orphan*/ ,void*,size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
cb_diskread(void *arg, int unit, uint64_t from, void *to, size_t size,
	    size_t *resid)
{
	ssize_t n;

	if (unit < 0 || unit >= ndisks )
		return (EIO);
	n = pread(disk_fd[unit], to, size, from);
	if (n < 0)
		return (errno);
	*resid = size - n;
	return (0);
}