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
typedef  int /*<<< orphan*/  fd_t ;
typedef  int dword_t ;

/* Variables and functions */
#define  F_GETLK64_ 130 
#define  F_SETLK64_ 129 
#define  F_SETLKW64_ 128 
 int _EINVAL ; 
 int sys_fcntl (int /*<<< orphan*/ ,int,int) ; 

dword_t sys_fcntl32(fd_t fd, dword_t cmd, dword_t arg) {
    switch (cmd) {
        case F_GETLK64_:
        case F_SETLK64_:
        case F_SETLKW64_:
            return _EINVAL;
    }
    return sys_fcntl(fd, cmd, arg);
}