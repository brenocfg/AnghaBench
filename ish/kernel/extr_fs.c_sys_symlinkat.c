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
typedef  int /*<<< orphan*/  target ;
struct fd {int dummy; } ;
typedef  int /*<<< orphan*/  link ;
typedef  int /*<<< orphan*/  fd_t ;
typedef  int /*<<< orphan*/  dword_t ;
typedef  int /*<<< orphan*/  addr_t ;

/* Variables and functions */
 int MAX_PATH ; 
 int /*<<< orphan*/  STRACE (char*,char*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  _EBADF ; 
 int /*<<< orphan*/  _EFAULT ; 
 struct fd* at_fd (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  generic_symlinkat (char*,struct fd*,char*) ; 
 scalar_t__ user_read_string (int /*<<< orphan*/ ,char*,int) ; 

dword_t sys_symlinkat(addr_t target_addr, fd_t at_f, addr_t link_addr) {
    char target[MAX_PATH];
    if (user_read_string(target_addr, target, sizeof(target)))
        return _EFAULT;
    char link[MAX_PATH];
    if (user_read_string(link_addr, link, sizeof(link)))
        return _EFAULT;
    STRACE("symlinkat(\"%s\", %d, \"%s\")", target, at_f, link);
    struct fd *at = at_fd(at_f);
    if (at == NULL)
        return _EBADF;
    return generic_symlinkat(target, at, link);
}