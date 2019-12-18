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
struct mount {int root_fd; } ;
struct attr {int type; int /*<<< orphan*/  size; int /*<<< orphan*/  mode; int /*<<< orphan*/  gid; int /*<<< orphan*/  uid; } ;

/* Variables and functions */
 int /*<<< orphan*/  TODO (char*) ; 
#define  attr_gid 131 
#define  attr_mode 130 
#define  attr_size 129 
#define  attr_uid 128 
 int errno_map () ; 
 int fchmodat (int,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int fchownat (int,char const*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 char* fix_path (char const*) ; 
 int realfs_truncate (struct mount*,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int realfs_setattr(struct mount *mount, const char *path, struct attr attr) {
    path = fix_path(path);
    int root = mount->root_fd;
    int err;
    switch (attr.type) {
        case attr_uid:
            err = fchownat(root, path, attr.uid, -1, 0);
            break;
        case attr_gid:
            err = fchownat(root, path, attr.gid, -1, 0);
            break;
        case attr_mode:
            err = fchmodat(root, path, attr.mode, 0);
            break;
        case attr_size:
            return realfs_truncate(mount, path, attr.size);
        default:
            TODO("other attrs");
    }
    if (err < 0)
        return errno_map();
    return err;
}