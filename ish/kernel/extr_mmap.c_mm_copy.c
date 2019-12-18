#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  lock; } ;
struct mm {int refcount; TYPE_1__ mem; int /*<<< orphan*/  exefile; } ;

/* Variables and functions */
 int /*<<< orphan*/  MEM_PAGES ; 
 int /*<<< orphan*/  fd_retain (int /*<<< orphan*/ ) ; 
 struct mm* malloc (int) ; 
 int /*<<< orphan*/  mem_init (TYPE_1__*) ; 
 int /*<<< orphan*/  pt_copy_on_write (TYPE_1__*,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  read_wrlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_wrunlock (int /*<<< orphan*/ *) ; 

struct mm *mm_copy(struct mm *mm) {
    struct mm *new_mm = malloc(sizeof(struct mm));
    if (new_mm == NULL)
        return NULL;
    *new_mm = *mm;
    new_mm->refcount = 1;
    mem_init(&new_mm->mem);
    fd_retain(new_mm->exefile);
    read_wrlock(&mm->mem.lock);
    pt_copy_on_write(&mm->mem, &new_mm->mem, 0, MEM_PAGES);
    read_wrunlock(&mm->mem.lock);
    return new_mm;
}