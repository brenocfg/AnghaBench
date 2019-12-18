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
struct fd {int /*<<< orphan*/  refcount; } ;
typedef  int /*<<< orphan*/  fd_t ;
typedef  int /*<<< orphan*/  dword_t ;

/* Variables and functions */
 int /*<<< orphan*/  STRACE (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _EBADF ; 
 struct fd* f_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  f_install (struct fd*,int /*<<< orphan*/ ) ; 

dword_t sys_dup(fd_t f) {
    STRACE("dup(%d)", f);
    struct fd *fd = f_get(f);
    if (fd == NULL)
        return _EBADF;
    fd->refcount++;
    return f_install(fd, 0);
}