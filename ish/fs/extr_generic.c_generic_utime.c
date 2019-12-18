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
struct timespec {int dummy; } ;
struct mount {TYPE_1__* fs; } ;
struct fd {int dummy; } ;
struct TYPE_2__ {int (* utime ) (struct mount*,char*,struct timespec,struct timespec) ;} ;

/* Variables and functions */
 int MAX_PATH ; 
 int /*<<< orphan*/  N_SYMLINK_FOLLOW ; 
 int /*<<< orphan*/  N_SYMLINK_NOFOLLOW ; 
 struct mount* find_mount_and_trim_path (char*) ; 
 int /*<<< orphan*/  mount_release (struct mount*) ; 
 int path_normalize (struct fd*,char const*,char*,int /*<<< orphan*/ ) ; 
 int stub1 (struct mount*,char*,struct timespec,struct timespec) ; 

int generic_utime(struct fd *at, const char *path_raw, struct timespec atime, struct timespec mtime, bool follow_links) {
    char path[MAX_PATH];
    int err = path_normalize(at, path_raw, path, follow_links ? N_SYMLINK_FOLLOW : N_SYMLINK_NOFOLLOW);
    if (err < 0)
        return err;
    struct mount *mount = find_mount_and_trim_path(path);
    err = mount->fs->utime(mount, path, atime, mtime);
    mount_release(mount);
    return err;
}