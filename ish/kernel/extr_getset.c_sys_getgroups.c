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
typedef  int /*<<< orphan*/  uid_t_ ;
typedef  int int_t ;
typedef  int dword_t ;
typedef  int /*<<< orphan*/  addr_t ;
struct TYPE_2__ {int ngroups; int /*<<< orphan*/  groups; } ;

/* Variables and functions */
 int _EFAULT ; 
 int _EINVAL ; 
 TYPE_1__* current ; 
 scalar_t__ user_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

int_t sys_getgroups(dword_t size, addr_t list) {
    if (size == 0)
        return current->ngroups;
    if (size < current->ngroups)
        return _EINVAL;
    if (user_write(list, current->groups, size * sizeof(uid_t_)))
        return _EFAULT;
    return 0;
}