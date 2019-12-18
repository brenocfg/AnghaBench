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
typedef  int /*<<< orphan*/  path ;
typedef  int /*<<< orphan*/  mode_t_ ;
typedef  int /*<<< orphan*/  dword_t ;
typedef  int /*<<< orphan*/  dev_t_ ;
typedef  int /*<<< orphan*/  addr_t ;

/* Variables and functions */
 int MAX_PATH ; 
 int /*<<< orphan*/  STRACE (char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _EFAULT ; 
 int /*<<< orphan*/  apply_umask (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  generic_mknod (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ user_read_string (int /*<<< orphan*/ ,char*,int) ; 

dword_t sys_mknod(addr_t path_addr, mode_t_ mode, dev_t_ dev) {
    char path[MAX_PATH];
    if (user_read_string(path_addr, path, sizeof(path)))
        return _EFAULT;
    STRACE("mknod(\"%s\", %#x, %#x)", path, mode, dev);
    apply_umask(&mode);
    return generic_mknod(path, mode, dev);
}