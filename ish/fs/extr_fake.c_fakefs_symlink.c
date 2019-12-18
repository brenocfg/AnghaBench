#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct mount {int /*<<< orphan*/  root_fd; } ;
struct ish_stat {int mode; scalar_t__ rdev; int /*<<< orphan*/  gid; int /*<<< orphan*/  uid; } ;
typedef  scalar_t__ ssize_t ;
struct TYPE_2__ {int /*<<< orphan*/  egid; int /*<<< orphan*/  euid; } ;

/* Variables and functions */
 int O_CREAT ; 
 int O_EXCL ; 
 int O_WRONLY ; 
 int S_IFLNK ; 
 int /*<<< orphan*/  close (int) ; 
 TYPE_1__* current ; 
 int /*<<< orphan*/  db_begin (struct mount*) ; 
 int /*<<< orphan*/  db_commit (struct mount*) ; 
 int /*<<< orphan*/  db_rollback (struct mount*) ; 
 int errno ; 
 int errno_map () ; 
 int /*<<< orphan*/  fix_path (char const*) ; 
 int openat (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  path_create (struct mount*,char const*,struct ish_stat*) ; 
 int /*<<< orphan*/  strlen (char const*) ; 
 int /*<<< orphan*/  unlinkat (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ write (int,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int fakefs_symlink(struct mount *mount, const char *target, const char *link) {
    db_begin(mount);
    // create a file containing the target
    int fd = openat(mount->root_fd, fix_path(link), O_WRONLY | O_CREAT | O_EXCL, 0666);
    if (fd < 0) {
        db_rollback(mount);
        return errno_map();
    }
    ssize_t res = write(fd, target, strlen(target));
    close(fd);
    if (res < 0) {
        int saved_errno = errno;
        unlinkat(mount->root_fd, fix_path(link), 0);
        db_rollback(mount);
        errno = saved_errno;
        return errno_map();
    }

    // customize the stat info so it looks like a link
    struct ish_stat ishstat;
    ishstat.mode = S_IFLNK | 0777; // symlinks always have full permissions
    ishstat.uid = current->euid;
    ishstat.gid = current->egid;
    ishstat.rdev = 0;
    path_create(mount, link, &ishstat);
    db_commit(mount);
    return 0;
}