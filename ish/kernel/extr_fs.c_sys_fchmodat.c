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
typedef  int /*<<< orphan*/  fd_t ;
typedef  int /*<<< orphan*/  dword_t ;
typedef  int /*<<< orphan*/  addr_t ;

/* Variables and functions */
 int MAX_PATH ; 
 int /*<<< orphan*/  STRACE (char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_IFMT ; 
 int /*<<< orphan*/  _EBADF ; 
 int /*<<< orphan*/  _EFAULT ; 
 struct fd* at_fd (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  generic_setattrat (struct fd*,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  make_attr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ user_read_string (int /*<<< orphan*/ ,char*,int) ; 

dword_t sys_fchmodat(fd_t at_f, addr_t path_addr, dword_t mode) {
    char path[MAX_PATH];
    if (user_read_string(path_addr, path, sizeof(path)))
        return _EFAULT;
    STRACE("fchmodat(%d, \"%s\", %o)", at_f, path, mode);
    struct fd *at = at_fd(at_f);
    if (at == NULL)
        return _EBADF;
    mode &= ~S_IFMT;
    return generic_setattrat(at, path, make_attr(mode, mode), true);
}