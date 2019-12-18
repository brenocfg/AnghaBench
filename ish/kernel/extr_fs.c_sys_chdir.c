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
struct fd {int dummy; } ;
typedef  int /*<<< orphan*/  path ;
typedef  int /*<<< orphan*/  dword_t ;
typedef  int /*<<< orphan*/  addr_t ;
struct TYPE_2__ {int /*<<< orphan*/  fs; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct fd*) ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  PTR_ERR (struct fd*) ; 
 int /*<<< orphan*/  STRACE (char*,char*) ; 
 int /*<<< orphan*/  _EFAULT ; 
 TYPE_1__* current ; 
 int /*<<< orphan*/  fs_chdir (int /*<<< orphan*/ ,struct fd*) ; 
 struct fd* open_dir (char*) ; 
 scalar_t__ user_read_string (int /*<<< orphan*/ ,char*,int) ; 

dword_t sys_chdir(addr_t path_addr) {
    char path[MAX_PATH];
    if (user_read_string(path_addr, path, sizeof(path)))
        return _EFAULT;
    STRACE("chdir(\"%s\")", path);

    struct fd *dir = open_dir(path);
    if (IS_ERR(dir))
        return PTR_ERR(dir);
    fs_chdir(current->fs, dir);
    return 0;
}