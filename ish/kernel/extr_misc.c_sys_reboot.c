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
typedef  int int_t ;

/* Variables and functions */
#define  REBOOT_CMD_CAD_OFF 129 
#define  REBOOT_CMD_CAD_ON 128 
 scalar_t__ REBOOT_MAGIC1 ; 
 int REBOOT_MAGIC2 ; 
 int REBOOT_MAGIC2A ; 
 int REBOOT_MAGIC2B ; 
 int REBOOT_MAGIC2C ; 
 int /*<<< orphan*/  STRACE (char*,int,int,int) ; 
 int _EINVAL ; 
 int _EPERM ; 
 int /*<<< orphan*/  superuser () ; 

int_t sys_reboot(int_t magic, int_t magic2, int_t cmd) {
    STRACE("reboot(%#x, %d, %d)", magic, magic2, cmd);
    if (!superuser())
        return _EPERM;
    if (magic != (int) REBOOT_MAGIC1 ||
            (magic2 != REBOOT_MAGIC2 &&
             magic2 != REBOOT_MAGIC2A &&
             magic2 != REBOOT_MAGIC2B &&
             magic2 != REBOOT_MAGIC2C))
        return _EINVAL;

    switch (cmd) {
        case REBOOT_CMD_CAD_ON:
        case REBOOT_CMD_CAD_OFF:
            return 0;
        default:
            return _EPERM;
    }
}