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
struct mount {TYPE_1__* fs; } ;
typedef  int /*<<< orphan*/  mode_t_ ;
typedef  int /*<<< orphan*/  dev_t_ ;
struct TYPE_2__ {int (* mknod ) (struct mount*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  AT_PWD ; 
 int MAX_PATH ; 
 int N_PARENT_DIR_WRITE ; 
 int N_SYMLINK_NOFOLLOW ; 
 scalar_t__ S_ISBLK (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISCHR (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISLNK (int /*<<< orphan*/ ) ; 
 int _EINVAL ; 
 int _EPERM ; 
 struct mount* find_mount_and_trim_path (char*) ; 
 int /*<<< orphan*/  mount_release (struct mount*) ; 
 int path_normalize (int /*<<< orphan*/ ,char const*,char*,int) ; 
 int stub1 (struct mount*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  superuser () ; 

int generic_mknod(const char *path_raw, mode_t_ mode, dev_t_ dev) {
    if (S_ISDIR(mode) || S_ISLNK(mode))
        return _EINVAL;
    if (!superuser() && (S_ISBLK(mode) || S_ISCHR(mode)))
        return _EPERM;

    char path[MAX_PATH];
    int err = path_normalize(AT_PWD, path_raw, path, N_SYMLINK_NOFOLLOW | N_PARENT_DIR_WRITE);
    if (err < 0)
        return err;
    struct mount *mount = find_mount_and_trim_path(path);
    if (mount->fs->mknod == NULL)
        err = _EPERM;
    else
        err = mount->fs->mknod(mount, path, mode, dev);
    mount_release(mount);
    return err;
}