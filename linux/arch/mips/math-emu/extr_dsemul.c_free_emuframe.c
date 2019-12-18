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
struct TYPE_3__ {int /*<<< orphan*/  bd_emupage_lock; int /*<<< orphan*/  bd_emupage_queue; int /*<<< orphan*/  bd_emupage_allocmap; } ;
struct mm_struct {TYPE_1__ context; } ;
typedef  TYPE_1__ mm_context_t ;
struct TYPE_4__ {int /*<<< orphan*/  pid; } ;

/* Variables and functions */
 int /*<<< orphan*/  bitmap_clear (int /*<<< orphan*/ ,int,int) ; 
 TYPE_2__* current ; 
 int /*<<< orphan*/  pr_debug (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void free_emuframe(int idx, struct mm_struct *mm)
{
	mm_context_t *mm_ctx = &mm->context;

	spin_lock(&mm_ctx->bd_emupage_lock);

	pr_debug("free emuframe %d from %d\n", idx, current->pid);
	bitmap_clear(mm_ctx->bd_emupage_allocmap, idx, 1);

	/* If some thread is waiting for a frame, now's its chance */
	wake_up(&mm_ctx->bd_emupage_queue);

	spin_unlock(&mm_ctx->bd_emupage_lock);
}