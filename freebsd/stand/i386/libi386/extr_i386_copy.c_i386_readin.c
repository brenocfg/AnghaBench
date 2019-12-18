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
typedef  scalar_t__ vm_offset_t ;
typedef  int ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  EFBIG ; 
 int /*<<< orphan*/  PTOV (scalar_t__) ; 
 int /*<<< orphan*/  errno ; 
 scalar_t__ memtop_copyin ; 
 int read (int const,int /*<<< orphan*/ ,size_t const) ; 

ssize_t
i386_readin(const int fd, vm_offset_t dest, const size_t len)
{

	if (dest + len >= memtop_copyin) {
		errno = EFBIG;
		return (-1);
	}

	return (read(fd, PTOV(dest), len));
}