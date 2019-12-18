#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct mount {int dummy; } ;
struct ish_stat {int mode; scalar_t__ rdev; int /*<<< orphan*/  gid; int /*<<< orphan*/  uid; } ;
struct fd {scalar_t__ fake_inode; int /*<<< orphan*/ * ops; } ;
struct TYPE_4__ {int /*<<< orphan*/  egid; int /*<<< orphan*/  euid; } ;
struct TYPE_3__ {struct fd* (* open ) (struct mount*,char const*,int,int) ;} ;

/* Variables and functions */
 struct fd* ERR_PTR (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (struct fd*) ; 
 int O_CREAT_ ; 
 int S_IFREG ; 
 int /*<<< orphan*/  _ENOENT ; 
 TYPE_2__* current ; 
 int /*<<< orphan*/  db_begin (struct mount*) ; 
 int /*<<< orphan*/  db_commit (struct mount*) ; 
 int /*<<< orphan*/  fakefs_fdops ; 
 int /*<<< orphan*/  fd_close (struct fd*) ; 
 int /*<<< orphan*/  path_create (struct mount*,char const*,struct ish_stat*) ; 
 void* path_get_inode (struct mount*,char const*) ; 
 TYPE_1__ realfs ; 
 struct fd* stub1 (struct mount*,char const*,int,int) ; 

__attribute__((used)) static struct fd *fakefs_open(struct mount *mount, const char *path, int flags, int mode) {
    struct fd *fd = realfs.open(mount, path, flags, 0666);
    if (IS_ERR(fd))
        return fd;
    db_begin(mount);
    fd->fake_inode = path_get_inode(mount, path);
    if (flags & O_CREAT_) {
        struct ish_stat ishstat;
        ishstat.mode = mode | S_IFREG;
        ishstat.uid = current->euid;
        ishstat.gid = current->egid;
        ishstat.rdev = 0;
        if (fd->fake_inode == 0) {
            path_create(mount, path, &ishstat);
            fd->fake_inode = path_get_inode(mount, path);
        }
    }
    db_commit(mount);
    if (fd->fake_inode == 0) {
        // metadata for this file is missing
        // TODO unlink the real file
        fd_close(fd);
        return ERR_PTR(_ENOENT);
    }
    fd->ops = &fakefs_fdops;
    return fd;
}