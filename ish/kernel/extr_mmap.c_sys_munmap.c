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
typedef  scalar_t__ uint_t ;
typedef  int /*<<< orphan*/  int_t ;
typedef  int /*<<< orphan*/  addr_t ;
struct TYPE_4__ {TYPE_1__* mem; } ;
struct TYPE_3__ {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PAGE_ROUND_UP (scalar_t__) ; 
 scalar_t__ PGOFFSET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STRACE (char*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  _EINVAL ; 
 TYPE_2__* current ; 
 int pt_unmap_always (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_wrlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_wrunlock (int /*<<< orphan*/ *) ; 

int_t sys_munmap(addr_t addr, uint_t len) {
    STRACE("munmap(0x%x, 0x%x)", addr, len);
    if (PGOFFSET(addr) != 0)
        return _EINVAL;
    if (len == 0)
        return _EINVAL;
    write_wrlock(&current->mem->lock);
    int err = pt_unmap_always(current->mem, PAGE(addr), PAGE_ROUND_UP(len));
    write_wrunlock(&current->mem->lock);
    if (err < 0)
        return _EINVAL;
    return 0;
}