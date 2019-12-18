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
typedef  int /*<<< orphan*/  vfp ;
struct thread {int dummy; } ;
typedef  int /*<<< orphan*/  mcontext_vfp_t ;

/* Variables and functions */
 int /*<<< orphan*/  NT_ARM_VFP ; 
 size_t elf32_populate_note (int /*<<< orphan*/ ,int /*<<< orphan*/ *,void*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_vfpcontext (struct thread*,int /*<<< orphan*/ *) ; 

void
elf32_dump_thread(struct thread *td, void *dst, size_t *off)
{
#ifdef VFP
	mcontext_vfp_t vfp;

	if (dst != NULL) {
		get_vfpcontext(td, &vfp);
		*off = elf32_populate_note(NT_ARM_VFP, &vfp, dst, sizeof(vfp),
		    NULL);
	} else
		*off = elf32_populate_note(NT_ARM_VFP, NULL, NULL, sizeof(vfp),
		    NULL);
#endif
}