#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct vm_area_struct {unsigned long vm_start; } ;
struct vdso_image {unsigned long sym_int80_landing_pad; } ;
struct pt_regs {unsigned long ip; } ;
struct TYPE_6__ {TYPE_2__* mm; } ;
struct TYPE_4__ {scalar_t__ vdso; } ;
struct TYPE_5__ {TYPE_1__ context; } ;

/* Variables and functions */
 TYPE_3__* current ; 
 struct pt_regs* current_pt_regs () ; 
 scalar_t__ in_ia32_syscall () ; 
 struct vdso_image const vdso_image_32 ; 

__attribute__((used)) static void vdso_fix_landing(const struct vdso_image *image,
		struct vm_area_struct *new_vma)
{
#if defined CONFIG_X86_32 || defined CONFIG_IA32_EMULATION
	if (in_ia32_syscall() && image == &vdso_image_32) {
		struct pt_regs *regs = current_pt_regs();
		unsigned long vdso_land = image->sym_int80_landing_pad;
		unsigned long old_land_addr = vdso_land +
			(unsigned long)current->mm->context.vdso;

		/* Fixing userspace landing - look at do_fast_syscall_32 */
		if (regs->ip == old_land_addr)
			regs->ip = new_vma->vm_start + vdso_land;
	}
#endif
}