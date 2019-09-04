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
typedef  int ssize_t ;
typedef  scalar_t__ off_t ;

/* Variables and functions */
 int /*<<< orphan*/  SEEK_CUR ; 
 int /*<<< orphan*/  SEEK_SET ; 
 scalar_t__ lseek (int,scalar_t__,int /*<<< orphan*/ ) ; 
 int read_in_full (int,void*,size_t) ; 

ssize_t git_pread(int fd, void *buf, size_t count, off_t offset)
{
        off_t current_offset;
        ssize_t rc;

        current_offset = lseek(fd, 0, SEEK_CUR);

        if (lseek(fd, offset, SEEK_SET) < 0)
                return -1;

        rc = read_in_full(fd, buf, count);

        if (current_offset != lseek(fd, current_offset, SEEK_SET))
                return -1;
        return rc;
}