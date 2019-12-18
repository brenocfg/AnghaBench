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
struct mm {int refcount; int /*<<< orphan*/ * exefile; scalar_t__ brk; scalar_t__ start_brk; int /*<<< orphan*/  mem; } ;

/* Variables and functions */
 struct mm* malloc (int) ; 
 int /*<<< orphan*/  mem_init (int /*<<< orphan*/ *) ; 

struct mm *mm_new() {
    struct mm *mm = malloc(sizeof(struct mm));
    if (mm == NULL)
        return NULL;
    mem_init(&mm->mem);
    mm->start_brk = mm->brk = 0; // should get overwritten by exec
    mm->exefile = NULL;
    mm->refcount = 1;
    return mm;
}