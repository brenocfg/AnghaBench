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
typedef  int /*<<< orphan*/  int_t ;
typedef  int /*<<< orphan*/  addr_t ;
struct TYPE_2__ {int /*<<< orphan*/  suid; int /*<<< orphan*/  euid; int /*<<< orphan*/  uid; } ;

/* Variables and functions */
 int /*<<< orphan*/  STRACE (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _EFAULT ; 
 TYPE_1__* current ; 
 scalar_t__ user_put (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int_t sys_getresuid(addr_t ruid_addr, addr_t euid_addr, addr_t suid_addr) {
    STRACE("getresuid(%#x, %#x, %#x)", ruid_addr, euid_addr, suid_addr);
    if (user_put(ruid_addr, current->uid))
        return _EFAULT;
    if (user_put(euid_addr, current->euid))
        return _EFAULT;
    if (user_put(suid_addr, current->suid))
        return _EFAULT;
    return 0;
}