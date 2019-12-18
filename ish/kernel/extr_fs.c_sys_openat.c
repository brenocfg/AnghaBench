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
struct fd {int dummy; } ;
typedef  int /*<<< orphan*/  path ;
typedef  int /*<<< orphan*/  mode_t_ ;
typedef  int /*<<< orphan*/  fd_t ;
typedef  int dword_t ;
typedef  int /*<<< orphan*/  addr_t ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct fd*) ; 
 int MAX_PATH ; 
 int O_CREAT_ ; 
 int /*<<< orphan*/  PTR_ERR (struct fd*) ; 
 int /*<<< orphan*/  STRACE (char*,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _EBADF ; 
 int /*<<< orphan*/  _EFAULT ; 
 int /*<<< orphan*/  apply_umask (int /*<<< orphan*/ *) ; 
 struct fd* at_fd (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  f_install (struct fd*,int) ; 
 struct fd* generic_openat (struct fd*,char*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ user_read_string (int /*<<< orphan*/ ,char*,int) ; 

fd_t sys_openat(fd_t at_f, addr_t path_addr, dword_t flags, mode_t_ mode) {
    char path[MAX_PATH];
    if (user_read_string(path_addr, path, sizeof(path)))
        return _EFAULT;
    STRACE("openat(%d, \"%s\", 0x%x, 0x%x)", at_f, path, flags, mode);

    if (flags & O_CREAT_)
        apply_umask(&mode);

    struct fd *at = at_fd(at_f);
    if (at == NULL)
        return _EBADF;
    struct fd *fd = generic_openat(at, path, flags, mode);
    if (IS_ERR(fd))
        return PTR_ERR(fd);
    return f_install(fd, flags);
}