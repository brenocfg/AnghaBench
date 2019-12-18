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
struct tlb_args {int /*<<< orphan*/  ta_start; int /*<<< orphan*/  ta_vma; } ;

/* Variables and functions */
 int /*<<< orphan*/  local_flush_tlb_page (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uaccess_restore (unsigned int) ; 
 unsigned int uaccess_save_and_enable () ; 

__attribute__((used)) static inline void ipi_flush_tlb_page(void *arg)
{
	struct tlb_args *ta = (struct tlb_args *)arg;
	unsigned int __ua_flags = uaccess_save_and_enable();

	local_flush_tlb_page(ta->ta_vma, ta->ta_start);

	uaccess_restore(__ua_flags);
}