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
struct exception_table_entry {int dummy; } ;
struct TYPE_3__ {unsigned long addr; } ;
struct TYPE_4__ {TYPE_1__ program_old_psw; } ;

/* Variables and functions */
 TYPE_2__ S390_lowcore ; 
 int /*<<< orphan*/  __ctl_load (unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __ctl_store (unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  disabled_wait () ; 
 unsigned long extable_fixup (struct exception_table_entry const*) ; 
 struct exception_table_entry* s390_search_extables (unsigned long) ; 

__attribute__((used)) static void early_pgm_check_handler(void)
{
	const struct exception_table_entry *fixup;
	unsigned long cr0, cr0_new;
	unsigned long addr;

	addr = S390_lowcore.program_old_psw.addr;
	fixup = s390_search_extables(addr);
	if (!fixup)
		disabled_wait();
	/* Disable low address protection before storing into lowcore. */
	__ctl_store(cr0, 0, 0);
	cr0_new = cr0 & ~(1UL << 28);
	__ctl_load(cr0_new, 0, 0);
	S390_lowcore.program_old_psw.addr = extable_fixup(fixup);
	__ctl_load(cr0, 0, 0);
}