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
struct fd {int dummy; } ;
struct TYPE_2__ {int (* link ) (struct mount*,char*,char*) ;} ;

/* Variables and functions */
 int MAX_PATH ; 
 int N_PARENT_DIR_WRITE ; 
 int N_SYMLINK_NOFOLLOW ; 
 int _EXDEV ; 
 struct mount* find_mount_and_trim_path (char*) ; 
 int /*<<< orphan*/  mount_release (struct mount*) ; 
 int path_normalize (struct fd*,char const*,char*,int) ; 
 int stub1 (struct mount*,char*,char*) ; 

int generic_linkat(struct fd *src_at, const char *src_raw, struct fd *dst_at, const char *dst_raw) {
    char src[MAX_PATH];
    int err = path_normalize(src_at, src_raw, src, N_SYMLINK_NOFOLLOW);
    if (err < 0)
        return err;
    char dst[MAX_PATH];
    err = path_normalize(dst_at, dst_raw, dst, N_SYMLINK_NOFOLLOW | N_PARENT_DIR_WRITE);
    if (err < 0)
        return err;
    struct mount *mount = find_mount_and_trim_path(src);
    struct mount *dst_mount = find_mount_and_trim_path(dst);
    if (mount != dst_mount)
        err = _EXDEV;
    else
        err = mount->fs->link(mount, src, dst);
    mount_release(mount);
    mount_release(dst_mount);
    return err;
}