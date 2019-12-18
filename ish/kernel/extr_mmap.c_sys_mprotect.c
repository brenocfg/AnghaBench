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
typedef  int /*<<< orphan*/  uint_t ;
typedef  int /*<<< orphan*/  pages_t ;
typedef  int int_t ;
typedef  int /*<<< orphan*/  addr_t ;
struct TYPE_4__ {TYPE_1__* mem; } ;
struct TYPE_3__ {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PAGE_ROUND_UP (int /*<<< orphan*/ ) ; 
 scalar_t__ PGOFFSET (int /*<<< orphan*/ ) ; 
 int P_RWX ; 
 int /*<<< orphan*/  STRACE (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int _EINVAL ; 
 TYPE_2__* current ; 
 int pt_set_flags (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  write_wrlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_wrunlock (int /*<<< orphan*/ *) ; 

int_t sys_mprotect(addr_t addr, uint_t len, int_t prot) {
    STRACE("mprotect(0x%x, 0x%x, 0x%x)", addr, len, prot);
    if (PGOFFSET(addr) != 0)
        return _EINVAL;
    if (prot & ~P_RWX)
        return _EINVAL;
    pages_t pages = PAGE_ROUND_UP(len);
    write_wrlock(&current->mem->lock);
    int err = pt_set_flags(current->mem, PAGE(addr), pages, prot);
    write_wrunlock(&current->mem->lock);
    return err;
}