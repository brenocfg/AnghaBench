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
struct TYPE_4__ {TYPE_1__* mm; } ;
struct TYPE_3__ {int /*<<< orphan*/  mmap_sem; } ;

/* Variables and functions */
 int SEGV_ACCERR ; 
 int SEGV_MAPERR ; 
 int /*<<< orphan*/  SIGSEGV ; 
 TYPE_2__* current ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * find_vma (TYPE_1__*,unsigned long) ; 
 int /*<<< orphan*/  force_signal_inject (int /*<<< orphan*/ ,int,unsigned long) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 

void arm64_notify_segfault(unsigned long addr)
{
	int code;

	down_read(&current->mm->mmap_sem);
	if (find_vma(current->mm, addr) == NULL)
		code = SEGV_MAPERR;
	else
		code = SEGV_ACCERR;
	up_read(&current->mm->mmap_sem);

	force_signal_inject(SIGSEGV, code, addr);
}