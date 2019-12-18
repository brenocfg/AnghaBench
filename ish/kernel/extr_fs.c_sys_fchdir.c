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
struct fd {int /*<<< orphan*/  refcount; } ;
typedef  int /*<<< orphan*/  fd_t ;
typedef  int /*<<< orphan*/  dword_t ;
struct TYPE_2__ {int /*<<< orphan*/  fs; } ;

/* Variables and functions */
 int /*<<< orphan*/  STRACE (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _EBADF ; 
 TYPE_1__* current ; 
 struct fd* f_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fs_chdir (int /*<<< orphan*/ ,struct fd*) ; 

dword_t sys_fchdir(fd_t f) {
    STRACE("fchdir(%d)", f);
    struct fd *dir = f_get(f);
    if (dir == NULL)
        return _EBADF;
    dir->refcount++;
    fs_chdir(current->fs, dir);
    return 0;
}