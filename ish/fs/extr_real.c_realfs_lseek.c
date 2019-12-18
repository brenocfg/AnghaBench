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
struct fd {int /*<<< orphan*/  real_fd; int /*<<< orphan*/ * dir; } ;
typedef  scalar_t__ off_t ;

/* Variables and functions */
 int LSEEK_CUR ; 
 int LSEEK_END ; 
 int LSEEK_SET ; 
 int SEEK_CUR ; 
 int SEEK_END ; 
 int SEEK_SET ; 
 scalar_t__ _EINVAL ; 
 scalar_t__ errno_map () ; 
 scalar_t__ lseek (int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  realfs_seekdir (struct fd*,scalar_t__) ; 

off_t realfs_lseek(struct fd *fd, off_t offset, int whence) {
    if (fd->dir != NULL && whence == LSEEK_SET) {
        realfs_seekdir(fd, offset);
        return offset;
    }

    if (whence == LSEEK_SET)
        whence = SEEK_SET;
    else if (whence == LSEEK_CUR)
        whence = SEEK_CUR;
    else if (whence == LSEEK_END)
        whence = SEEK_END;
    else
        return _EINVAL;
    off_t res = lseek(fd->real_fd, offset, whence);
    if (res < 0)
        return errno_map();
    return res;
}