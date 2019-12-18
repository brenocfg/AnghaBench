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
struct mm {scalar_t__ refcount; int /*<<< orphan*/  mem; int /*<<< orphan*/ * exefile; } ;

/* Variables and functions */
 int /*<<< orphan*/  fd_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (struct mm*) ; 
 int /*<<< orphan*/  mem_destroy (int /*<<< orphan*/ *) ; 

void mm_release(struct mm *mm) {
    if (--mm->refcount == 0) {
        if (mm->exefile != NULL)
            fd_close(mm->exefile);
        mem_destroy(&mm->mem);
        free(mm);
    }
}