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
struct statbuf {int mode; int /*<<< orphan*/  rdev; int /*<<< orphan*/  inode; } ;
struct mount {TYPE_1__* fs; } ;
struct fd {int type; int flags; int /*<<< orphan*/  inode; struct mount* mount; } ;
struct TYPE_2__ {int (* fstat ) (struct fd*,struct statbuf*) ;struct fd* (* open ) (struct mount*,char*,int,int) ;} ;

/* Variables and functions */
 int AC_R ; 
 int AC_W ; 
 int DEV_BLOCK ; 
 int DEV_CHAR ; 
 struct fd* ERR_PTR (int) ; 
 scalar_t__ IS_ERR (struct fd*) ; 
 int MAX_PATH ; 
 int N_PARENT_DIR_WRITE ; 
 int N_SYMLINK_FOLLOW ; 
 int O_CREAT_ ; 
 int O_DIRECTORY_ ; 
 int O_RDWR_ ; 
 int O_WRONLY_ ; 
 int S_IFMT ; 
 scalar_t__ S_ISBLK (int) ; 
 scalar_t__ S_ISCHR (int) ; 
 scalar_t__ S_ISDIR (int) ; 
 int /*<<< orphan*/  S_ISLNK (int) ; 
 scalar_t__ S_ISSOCK (int) ; 
 int _EINVAL ; 
 int _EISDIR ; 
 int _ENOTDIR ; 
 int _ENXIO ; 
 int access_check (struct statbuf*,int) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  dev_major (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_minor (int /*<<< orphan*/ ) ; 
 int dev_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct fd*) ; 
 int /*<<< orphan*/  fd_close (struct fd*) ; 
 struct mount* find_mount_and_trim_path (char*) ; 
 int /*<<< orphan*/  inode_get (struct mount*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mount_release (struct mount*) ; 
 int path_normalize (struct fd*,char const*,char*,int) ; 
 struct fd* stub1 (struct mount*,char*,int,int) ; 
 int stub2 (struct fd*,struct statbuf*) ; 

struct fd *generic_openat(struct fd *at, const char *path_raw, int flags, int mode) {
    if (flags & O_RDWR_ && flags & O_WRONLY_)
        return ERR_PTR(_EINVAL);

    // TODO really, really, seriously reconsider what I'm doing with the strings
    char path[MAX_PATH];
    int err = path_normalize(at, path_raw, path, N_SYMLINK_FOLLOW |
            (flags & O_CREAT_ ? N_PARENT_DIR_WRITE : 0));
    if (err < 0)
        return ERR_PTR(err);
    struct mount *mount = find_mount_and_trim_path(path);
    struct fd *fd = mount->fs->open(mount, path, flags, mode);
    if (IS_ERR(fd)) {
        // if an error happens after this point, fd_close will release the
        // mount, but right now we need to do it manually
        mount_release(mount);
        return fd;
    }
    fd->mount = mount;

    struct statbuf stat;
    err = fd->mount->fs->fstat(fd, &stat);
    if (err < 0)
        goto error;
    fd->inode = inode_get(mount, stat.inode);
    fd->type = stat.mode & S_IFMT;
    fd->flags = flags;

    int accmode;
    if (flags & O_RDWR_) accmode = AC_R | AC_W;
    else if (flags & O_WRONLY_) accmode = AC_W;
    else accmode = AC_R;
    err = access_check(&stat, accmode);
    if (err < 0)
        goto error;

    assert(!S_ISLNK(fd->type)); // would mean path_normalize didn't do its job
    if (S_ISBLK(fd->type) || S_ISCHR(fd->type)) {
        int type;
        if (S_ISBLK(fd->type))
            type = DEV_BLOCK;
        else
            type = DEV_CHAR;
        err = dev_open(dev_major(stat.rdev), dev_minor(stat.rdev), type, fd);
        if (err < 0)
            goto error;
    }
    err = _ENXIO;
    if (S_ISSOCK(fd->type))
        goto error;
    err = _EISDIR;
    if (S_ISDIR(fd->type) && flags & (O_RDWR_ | O_WRONLY_))
        goto error;
    err = _ENOTDIR;
    if (!S_ISDIR(fd->type) && flags & O_DIRECTORY_)
        goto error;
    return fd;

error:
    fd_close(fd);
    return ERR_PTR(err);
}