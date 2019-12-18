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
struct robust_list_head_ {int dummy; } ;
typedef  int /*<<< orphan*/  int_t ;
typedef  int dword_t ;
typedef  int /*<<< orphan*/  addr_t ;
struct TYPE_2__ {int /*<<< orphan*/  robust_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  STRACE (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  _EINVAL ; 
 TYPE_1__* current ; 

int_t sys_set_robust_list(addr_t robust_list, dword_t len) {
    STRACE("set_robust_list(%#x, %d)", robust_list, len);
    if (len != sizeof(struct robust_list_head_))
        return _EINVAL;
    current->robust_list = robust_list;
    return 0;
}