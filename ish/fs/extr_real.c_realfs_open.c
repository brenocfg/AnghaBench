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
struct fd {int real_fd; int /*<<< orphan*/ * dir; } ;

/* Variables and functions */
 struct fd* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno_map () ; 
 struct fd* fd_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fix_path (char const*) ; 
 int open_flags_real_from_fake (int) ; 
 int openat (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  realfs_fdops ; 

__attribute__((used)) static struct fd *realfs_open(struct mount *mount, const char *path, int flags, int mode) {
    int real_flags = open_flags_real_from_fake(flags);
    int fd_no = openat(mount->root_fd, fix_path(path), real_flags, mode);
    if (fd_no < 0)
        return ERR_PTR(errno_map());
    struct fd *fd = fd_create(&realfs_fdops);
    fd->real_fd = fd_no;
    fd->dir = NULL;
    return fd;
}