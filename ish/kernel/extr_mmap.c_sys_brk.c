#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  lock; } ;
struct mm {scalar_t__ start_brk; scalar_t__ brk; TYPE_1__ mem; } ;
typedef  scalar_t__ addr_t ;
struct TYPE_5__ {struct mm* mm; } ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE (scalar_t__) ; 
 scalar_t__ PAGE_ROUND_UP (scalar_t__) ; 
 int /*<<< orphan*/  P_WRITE ; 
 int /*<<< orphan*/  STRACE (char*,scalar_t__) ; 
 scalar_t__ _EINVAL ; 
 TYPE_3__* current ; 
 int pt_map_nothing (TYPE_1__*,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pt_unmap_always (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_wrlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_wrunlock (int /*<<< orphan*/ *) ; 

addr_t sys_brk(addr_t new_brk) {
    STRACE("brk(0x%x)", new_brk);
    struct mm *mm = current->mm;

    if (new_brk != 0 && new_brk < mm->start_brk)
        return _EINVAL;
    write_wrlock(&mm->mem.lock);
    addr_t old_brk = mm->brk;
    if (new_brk == 0) {
        write_wrunlock(&mm->mem.lock);
        return old_brk;
    }
    // TODO check for not going too high

    if (new_brk > old_brk) {
        // expand heap: map region from old_brk to new_brk
        int err = pt_map_nothing(&mm->mem, PAGE_ROUND_UP(old_brk),
                PAGE_ROUND_UP(new_brk) - PAGE_ROUND_UP(old_brk), P_WRITE);
        if (err < 0) {
            write_wrunlock(&mm->mem.lock);
            return err;
        }
    } else if (new_brk < old_brk) {
        // shrink heap: unmap region from new_brk to old_brk
        // first page to unmap is PAGE(new_brk)
        // last page to unmap is PAGE(old_brk)
        pt_unmap_always(&mm->mem, PAGE(new_brk), PAGE(old_brk));
    }

    mm->brk = new_brk;
    write_wrunlock(&mm->mem.lock);
    return new_brk;
}