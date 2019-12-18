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
struct user_segment_descriptor {int dummy; } ;
struct thread {struct pcb* td_pcb; } ;
struct pcb {scalar_t__ pcb_gsbase; } ;
struct linux_set_thread_area_args {int /*<<< orphan*/  desc; } ;
struct l_user_desc {int entry_number; scalar_t__ base_addr; } ;
typedef  scalar_t__ register_t ;
typedef  int /*<<< orphan*/  a ;

/* Variables and functions */
 int EINVAL ; 
#define  GUDATA_SEL 129 
#define  GUGS32_SEL 128 
 scalar_t__ LINUX_LDT_empty (struct l_user_desc*) ; 
 int LINUX_LDT_entry_a (struct l_user_desc*) ; 
 int LINUX_LDT_entry_b (struct l_user_desc*) ; 
 int /*<<< orphan*/  PCB_32BIT ; 
 int copyin (int /*<<< orphan*/ ,struct l_user_desc*,int) ; 
 int copyout (struct l_user_desc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memcpy (struct user_segment_descriptor*,int**,int) ; 
 int /*<<< orphan*/  set_pcb_flags (struct pcb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  update_gdt_gsbase (struct thread*,scalar_t__) ; 

int
linux_set_thread_area(struct thread *td,
    struct linux_set_thread_area_args *args)
{
	struct l_user_desc info;
	struct user_segment_descriptor sd;
	struct pcb *pcb;
	int a[2];
	int error;

	error = copyin(args->desc, &info, sizeof(struct l_user_desc));
	if (error)
		return (error);

	/*
	 * Semantics of Linux version: every thread in the system has array
	 * of three TLS descriptors. 1st is GLIBC TLS, 2nd is WINE, 3rd unknown.
	 * This syscall loads one of the selected TLS decriptors with a value
	 * and also loads GDT descriptors 6, 7 and 8 with the content of
	 * the per-thread descriptors.
	 *
	 * Semantics of FreeBSD version: I think we can ignore that Linux has
	 * three per-thread descriptors and use just the first one.
	 * The tls_array[] is used only in [gs]et_thread_area() syscalls and
	 * for loading the GDT descriptors. We use just one GDT descriptor
	 * for TLS, so we will load just one.
	 *
	 * XXX: This doesn't work when a user space process tries to use more
	 * than one TLS segment. Comment in the Linux source says wine might
	 * do this.
	 */

	/*
	 * GLIBC reads current %gs and call set_thread_area() with it.
	 * We should let GUDATA_SEL and GUGS32_SEL proceed as well because
	 * we use these segments.
	 */
	switch (info.entry_number) {
	case GUGS32_SEL:
	case GUDATA_SEL:
	case 6:
	case -1:
		info.entry_number = GUGS32_SEL;
		break;
	default:
		return (EINVAL);
	}

	/*
	 * We have to copy out the GDT entry we use.
	 *
	 * XXX: What if a user space program does not check the return value
	 * and tries to use 6, 7 or 8?
	 */
	error = copyout(&info, args->desc, sizeof(struct l_user_desc));
	if (error)
		return (error);

	if (LINUX_LDT_empty(&info)) {
		a[0] = 0;
		a[1] = 0;
	} else {
		a[0] = LINUX_LDT_entry_a(&info);
		a[1] = LINUX_LDT_entry_b(&info);
	}

	memcpy(&sd, &a, sizeof(a));
	pcb = td->td_pcb;
	pcb->pcb_gsbase = (register_t)info.base_addr;
	set_pcb_flags(pcb, PCB_32BIT);
	update_gdt_gsbase(td, info.base_addr);

	return (0);
}