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
struct TYPE_2__ {scalar_t__ md_spinlock_count; int /*<<< orphan*/  md_saved_pil; } ;
struct thread {TYPE_1__ td_md; } ;
typedef  int /*<<< orphan*/  register_t ;

/* Variables and functions */
 int /*<<< orphan*/  critical_exit () ; 
 struct thread* curthread ; 
 int /*<<< orphan*/  wrpr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
spinlock_exit(void)
{
	struct thread *td;
	register_t pil;

	td = curthread;
	critical_exit();
	pil = td->td_md.md_saved_pil;
	td->td_md.md_spinlock_count--;
	if (td->td_md.md_spinlock_count == 0)
		wrpr(pil, pil, 0);
}