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
struct TYPE_2__ {scalar_t__ md_stack_base; } ;
struct thread {int td_kstack_pages; scalar_t__ td_kstack; TYPE_1__ td_md; } ;

/* Variables and functions */
 int PAGE_SIZE ; 
 int /*<<< orphan*/  XSAVE_AREA_ALIGN ; 
 int /*<<< orphan*/  cpu_max_ext_state_size ; 
 scalar_t__ roundup2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
set_top_of_stack_td(struct thread *td)
{
	td->td_md.md_stack_base = td->td_kstack +
	    td->td_kstack_pages * PAGE_SIZE -
	    roundup2(cpu_max_ext_state_size, XSAVE_AREA_ALIGN);
}