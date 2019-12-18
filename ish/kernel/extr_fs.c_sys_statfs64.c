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
struct statfs64_ {int dummy; } ;
struct mount {int dummy; } ;
typedef  int /*<<< orphan*/  path_raw ;
typedef  int dword_t ;
typedef  int /*<<< orphan*/  addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  AT_PWD ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  N_SYMLINK_NOFOLLOW ; 
 int /*<<< orphan*/  STRACE (char*,char*,int,int /*<<< orphan*/ ) ; 
 int _EFAULT ; 
 int _EINVAL ; 
 struct mount* mount_find (char*) ; 
 int /*<<< orphan*/  mount_release (struct mount*) ; 
 int path_normalize (int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ ) ; 
 int statfs64_mount (struct mount*,int /*<<< orphan*/ ) ; 
 scalar_t__ user_read_string (int /*<<< orphan*/ ,char*,int) ; 

dword_t sys_statfs64(addr_t path_addr, dword_t buf_size, addr_t buf_addr) {
    char path_raw[MAX_PATH];
    if (user_read_string(path_addr, path_raw, sizeof(path_raw)))
        return _EFAULT;
    STRACE("statfs64(\"%s\", %d, %#x)", path_raw, buf_size, buf_addr);
    if (buf_size != sizeof(struct statfs64_))
        return _EINVAL;
    char path[MAX_PATH];
    int err = path_normalize(AT_PWD, path_raw, path, N_SYMLINK_NOFOLLOW);
    if (err < 0)
        return err;
    struct mount *mount = mount_find(path);
    err = statfs64_mount(mount, buf_addr);
    mount_release(mount);
    return err;
}