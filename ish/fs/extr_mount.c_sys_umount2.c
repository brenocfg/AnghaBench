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
typedef  int /*<<< orphan*/  target_raw ;
typedef  int dword_t ;
typedef  int /*<<< orphan*/  addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  AT_PWD ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  N_SYMLINK_FOLLOW ; 
 int /*<<< orphan*/  N_SYMLINK_NOFOLLOW ; 
 int UMOUNT_NOFOLLOW_ ; 
 int _EFAULT ; 
 int do_umount (char*) ; 
 int /*<<< orphan*/  lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mounts_lock ; 
 int path_normalize (int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ user_read_string (int /*<<< orphan*/ ,char*,int) ; 

dword_t sys_umount2(addr_t target_addr, dword_t flags) {
    char target_raw[MAX_PATH];
    if (user_read_string(target_addr, target_raw, sizeof(target_raw)))
        return _EFAULT;
    char target[MAX_PATH];
    int err = path_normalize(AT_PWD, target_raw, target,
            flags & UMOUNT_NOFOLLOW_ ? N_SYMLINK_NOFOLLOW : N_SYMLINK_FOLLOW);
    if (err < 0)
        return err;

    lock(&mounts_lock);
    err = do_umount(target);
    unlock(&mounts_lock);
    return err;
}