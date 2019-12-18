#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct fd {int dummy; } ;
typedef  int dword_t ;
typedef  int /*<<< orphan*/  addr_t ;
struct TYPE_4__ {TYPE_1__* fs; } ;
struct TYPE_3__ {int /*<<< orphan*/  lock; struct fd* pwd; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAX_PATH ; 
 int /*<<< orphan*/  STRACE (char*,int,...) ; 
 int _EFAULT ; 
 int _ENOMEM ; 
 int _ERANGE ; 
 TYPE_2__* current ; 
 int /*<<< orphan*/  free (char*) ; 
 int generic_getpath (struct fd*,char*) ; 
 int /*<<< orphan*/  lock (int /*<<< orphan*/ *) ; 
 char* malloc (int) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ user_write (int /*<<< orphan*/ ,char*,int) ; 

dword_t sys_getcwd(addr_t buf_addr, dword_t size) {
    STRACE("getcwd(%#x, %#x)", buf_addr, size);
    lock(&current->fs->lock);
    struct fd *wd = current->fs->pwd;
    char pwd[MAX_PATH + 1];
    int err = generic_getpath(wd, pwd);
    unlock(&current->fs->lock);
    if (err < 0)
        return err;

    if (strlen(pwd) + 1 > size)
        return _ERANGE;
    size = strlen(pwd) + 1;
    char *buf = malloc(size);
    if (buf == NULL)
        return _ENOMEM;
    strcpy(buf, pwd);
    STRACE(" \"%.*s\"", size, buf);
    dword_t res = size;
    if (user_write(buf_addr, buf, size))
        res = _EFAULT;
    free(buf);
    return res;
}