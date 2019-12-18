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
typedef  scalar_t__ vm_offset_t ;
struct thread {int td_kstack_pages; scalar_t__ td_kstack; } ;
struct pcb {int dummy; } ;

/* Variables and functions */
 int PAGE_SIZE ; 
 int /*<<< orphan*/  XSAVE_AREA_ALIGN ; 
 int /*<<< orphan*/  cpu_max_ext_state_size ; 
 scalar_t__ roundup2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

struct pcb *
get_pcb_td(struct thread *td)
{
	vm_offset_t p;

	p = td->td_kstack + td->td_kstack_pages * PAGE_SIZE -
	    roundup2(cpu_max_ext_state_size, XSAVE_AREA_ALIGN) -
	    sizeof(struct pcb);
	return ((struct pcb *)p);
}