#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct ldt_struct {unsigned int nr_entries; struct desc_struct* entries; } ;
struct desc_struct {int dummy; } ;
struct TYPE_8__ {TYPE_2__* active_mm; } ;
struct TYPE_7__ {int /*<<< orphan*/  gdt; } ;
struct TYPE_5__ {int /*<<< orphan*/  ldt; } ;
struct TYPE_6__ {TYPE_1__ context; } ;

/* Variables and functions */
 unsigned int GDT_ENTRIES ; 
 struct ldt_struct* READ_ONCE (int /*<<< orphan*/ ) ; 
 unsigned int SEGMENT_LDT ; 
 unsigned int SEGMENT_TI_MASK ; 
 TYPE_4__* current ; 
 TYPE_3__ gdt_page ; 
 unsigned long get_desc_base (struct desc_struct*) ; 
 struct desc_struct* raw_cpu_ptr (int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned long get_segment_base(unsigned int segment)
{
	struct desc_struct *desc;
	unsigned int idx = segment >> 3;

	if ((segment & SEGMENT_TI_MASK) == SEGMENT_LDT) {
#ifdef CONFIG_MODIFY_LDT_SYSCALL
		struct ldt_struct *ldt;

		/* IRQs are off, so this synchronizes with smp_store_release */
		ldt = READ_ONCE(current->active_mm->context.ldt);
		if (!ldt || idx >= ldt->nr_entries)
			return 0;

		desc = &ldt->entries[idx];
#else
		return 0;
#endif
	} else {
		if (idx >= GDT_ENTRIES)
			return 0;

		desc = raw_cpu_ptr(gdt_page.gdt) + idx;
	}

	return get_desc_base(desc);
}