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
typedef  int vm_offset_t ;
struct TYPE_2__ {int md_stack_base; } ;
struct thread {TYPE_1__ td_md; } ;
struct savefpu {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int XSAVE_AREA_ALIGN ; 

struct savefpu *
get_pcb_user_save_td(struct thread *td)
{
	vm_offset_t p;

	p = td->td_md.md_stack_base;
	KASSERT((p % XSAVE_AREA_ALIGN) == 0,
	    ("Unaligned pcb_user_save area ptr %#lx td %p", p, td));
	return ((struct savefpu *)p);
}