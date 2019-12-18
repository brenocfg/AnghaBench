#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  int u_int ;
struct TYPE_3__ {scalar_t__ r_offset; int /*<<< orphan*/  r_info; } ;
typedef  TYPE_1__ Elf_Rel ;
typedef  int /*<<< orphan*/  Elf_Addr ;

/* Variables and functions */
 int ELF_R_TYPE (int /*<<< orphan*/ ) ; 
#define  R_386_IRELATIVE 128 
 int /*<<< orphan*/  cpuid_count (int,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  do_cpuid (int,int*) ; 
 int /*<<< orphan*/  stub1 (int,int,int,int) ; 

__attribute__((used)) static void
crt1_handle_rel(const Elf_Rel *r)
{
	Elf_Addr *where, target;
	u_int cpuid_supported, p[4];
	uint32_t cpu_feature, cpu_feature2;
	uint32_t cpu_stdext_feature, cpu_stdext_feature2;

	__asm __volatile(
	    "	pushfl\n"
	    "	popl	%%eax\n"
	    "	movl    %%eax,%%ecx\n"
	    "	xorl    $0x200000,%%eax\n"
	    "	pushl	%%eax\n"
	    "	popfl\n"
	    "	pushfl\n"
	    "	popl    %%eax\n"
	    "	xorl    %%eax,%%ecx\n"
	    "	je	1f\n"
	    "	movl	$1,%0\n"
	    "	jmp	2f\n"
	    "1:	movl	$0,%0\n"
	    "2:\n"
	    : "=r" (cpuid_supported) : : "eax", "ecx", "cc");
	if (cpuid_supported) {
		do_cpuid(1, p);
		cpu_feature = p[3];
		cpu_feature2 = p[2];
		do_cpuid(0, p);
		if (p[0] >= 7) {
			cpuid_count(7, 0, p);
			cpu_stdext_feature = p[1];
			cpu_stdext_feature2 = p[2];
		} else {
			cpu_stdext_feature = 0;
			cpu_stdext_feature2 = 0;
		}
	} else {
		cpu_feature = 0;
		cpu_feature2 = 0;
		cpu_stdext_feature = 0;
		cpu_stdext_feature2 = 0;
	}

	switch (ELF_R_TYPE(r->r_info)) {
	case R_386_IRELATIVE:
		where = (Elf_Addr *)r->r_offset;
		target = ((Elf_Addr (*)(uint32_t, uint32_t, uint32_t,
		    uint32_t))*where)(cpu_feature, cpu_feature2,
		    cpu_stdext_feature, cpu_stdext_feature2);
		*where = target;
		break;
	}
}