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
typedef  int /*<<< orphan*/  src ;
typedef  int /*<<< orphan*/  fd_t ;
typedef  int /*<<< orphan*/  dword_t ;
typedef  int /*<<< orphan*/  dst ;
typedef  int /*<<< orphan*/  addr_t ;

/* Variables and functions */
 int MAX_PATH ; 
 int /*<<< orphan*/  STRACE (char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  _EBADF ; 
 int /*<<< orphan*/  _EFAULT ; 
 struct fd* at_fd (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  generic_linkat (struct fd*,char*,struct fd*,char*) ; 
 scalar_t__ user_read_string (int /*<<< orphan*/ ,char*,int) ; 

dword_t sys_linkat(fd_t src_at_f, addr_t src_addr, fd_t dst_at_f, addr_t dst_addr) {
    char src[MAX_PATH];
    if (user_read_string(src_addr, src, sizeof(src)))
        return _EFAULT;
    char dst[MAX_PATH];
    if (user_read_string(dst_addr, dst, sizeof(dst)))
        return _EFAULT;
    STRACE("linkat(%d, \"%s\", %d, \"%s\")", src_at_f, src, dst_at_f, dst);
    struct fd *src_at = at_fd(src_at_f);
    if (src_at == NULL)
        return _EBADF;
    struct fd *dst_at = at_fd(dst_at_f);
    if (dst_at == NULL)
        return _EBADF;
    return generic_linkat(src_at, src, dst_at, dst);
}