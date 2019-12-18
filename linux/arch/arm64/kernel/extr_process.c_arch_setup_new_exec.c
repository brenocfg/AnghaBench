#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_2__* mm; } ;
struct TYPE_5__ {int /*<<< orphan*/  flags; } ;
struct TYPE_6__ {TYPE_1__ context; } ;

/* Variables and functions */
 int /*<<< orphan*/  MMCF_AARCH32 ; 
 TYPE_3__* current ; 
 scalar_t__ is_compat_task () ; 
 int /*<<< orphan*/  ptrauth_thread_init_user (TYPE_3__*) ; 

void arch_setup_new_exec(void)
{
	current->mm->context.flags = is_compat_task() ? MMCF_AARCH32 : 0;

	ptrauth_thread_init_user(current);
}