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
struct mount {int /*<<< orphan*/  root_fd; } ;
typedef  int /*<<< orphan*/  off_t_ ;

/* Variables and functions */
 int /*<<< orphan*/  O_RDWR ; 
 int /*<<< orphan*/  close (int) ; 
 int errno_map () ; 
 int /*<<< orphan*/  fix_path (char const*) ; 
 scalar_t__ ftruncate (int,int /*<<< orphan*/ ) ; 
 int openat (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int realfs_truncate(struct mount *mount, const char *path, off_t_ size) {
    int fd = openat(mount->root_fd, fix_path(path), O_RDWR);
    if (fd < 0)
        return errno_map();
    int err = 0;
    if (ftruncate(fd, size) < 0)
        err = errno_map();
    close(fd);
    return err;
}