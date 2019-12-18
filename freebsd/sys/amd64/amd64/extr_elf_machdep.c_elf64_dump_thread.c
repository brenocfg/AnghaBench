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
typedef  int /*<<< orphan*/  uint64_t ;
struct thread {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NT_X86_XSTATE ; 
 int X86_XSTATE_XCR0_OFFSET ; 
 int /*<<< orphan*/  cpu_max_ext_state_size ; 
 scalar_t__ elf64_populate_note (int /*<<< orphan*/ ,int /*<<< orphan*/ *,void*,int /*<<< orphan*/ ,void**) ; 
 int /*<<< orphan*/  fpugetregs (struct thread*) ; 
 int /*<<< orphan*/ * get_pcb_user_save_td (struct thread*) ; 
 scalar_t__ use_xsave ; 
 int /*<<< orphan*/  xsave_mask ; 

void
elf64_dump_thread(struct thread *td, void *dst, size_t *off)
{
	void *buf;
	size_t len;

	len = 0;
	if (use_xsave) {
		if (dst != NULL) {
			fpugetregs(td);
			len += elf64_populate_note(NT_X86_XSTATE,
			    get_pcb_user_save_td(td), dst,
			    cpu_max_ext_state_size, &buf);
			*(uint64_t *)((char *)buf + X86_XSTATE_XCR0_OFFSET) =
			    xsave_mask;
		} else
			len += elf64_populate_note(NT_X86_XSTATE, NULL, NULL,
			    cpu_max_ext_state_size, NULL);
	}
	*off = len;
}