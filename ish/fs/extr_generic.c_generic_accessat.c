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
struct statbuf {int dummy; } ;
struct mount {TYPE_1__* fs; } ;
struct fd {int dummy; } ;
struct TYPE_2__ {int (* stat ) (struct mount*,char*,struct statbuf*,int) ;} ;

/* Variables and functions */
 int MAX_PATH ; 
 int /*<<< orphan*/  N_SYMLINK_FOLLOW ; 
 int access_check (struct statbuf*,int) ; 
 struct mount* find_mount_and_trim_path (char*) ; 
 int /*<<< orphan*/  mount_release (struct mount*) ; 
 int path_normalize (struct fd*,char const*,char*,int /*<<< orphan*/ ) ; 
 int stub1 (struct mount*,char*,struct statbuf*,int) ; 

int generic_accessat(struct fd *dirfd, const char *path_raw, int mode) {
    char path[MAX_PATH];
    int err = path_normalize(dirfd, path_raw, path, N_SYMLINK_FOLLOW);
    if (err < 0)
        return err;

    struct mount *mount = find_mount_and_trim_path(path);
    struct statbuf stat = {};
    err = mount->fs->stat(mount, path, &stat, true);
    mount_release(mount);
    if (err < 0)
        return err;
    return access_check(&stat, mode);
}