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
struct ptunit_suite {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  bound ; 
 int /*<<< orphan*/  call_9a_cd ; 
 int /*<<< orphan*/  call_9a_cp ; 
 int /*<<< orphan*/  call_ff_3 ; 
 int /*<<< orphan*/  evex_cutoff ; 
 int /*<<< orphan*/  int3 ; 
 int /*<<< orphan*/  intn ; 
 int /*<<< orphan*/  iret ; 
 int /*<<< orphan*/  jmp_ea_cd ; 
 int /*<<< orphan*/  jmp_ea_cp ; 
 int /*<<< orphan*/  jmp_ff_5 ; 
 int /*<<< orphan*/  jmp_rel ; 
 int /*<<< orphan*/  jrcxz ; 
 int /*<<< orphan*/  lds ; 
 int /*<<< orphan*/  lds_disp16 ; 
 int /*<<< orphan*/  lds_disp32 ; 
 int /*<<< orphan*/  lds_ind_disp16 ; 
 int /*<<< orphan*/  lds_ind_disp32 ; 
 int /*<<< orphan*/  lds_ind_disp8 ; 
 int /*<<< orphan*/  les ; 
 int /*<<< orphan*/  les_disp16 ; 
 int /*<<< orphan*/  les_disp32 ; 
 int /*<<< orphan*/  les_ind_disp16 ; 
 int /*<<< orphan*/  les_ind_disp32 ; 
 int /*<<< orphan*/  les_ind_disp8 ; 
 int /*<<< orphan*/  long_nop ; 
 int /*<<< orphan*/  mov_al_16 ; 
 int /*<<< orphan*/  mov_al_16_em32 ; 
 int /*<<< orphan*/  mov_al_32 ; 
 int /*<<< orphan*/  mov_al_32_em16 ; 
 int /*<<< orphan*/  mov_al_32_em64 ; 
 int /*<<< orphan*/  mov_al_64 ; 
 int /*<<< orphan*/  mov_ax_moffs16 ; 
 int /*<<< orphan*/  mov_ax_moffs32 ; 
 int /*<<< orphan*/  mov_ax_moffs64 ; 
 int /*<<< orphan*/  mov_ax_moffs64_32 ; 
 int /*<<< orphan*/  mov_eax_moffs32 ; 
 int /*<<< orphan*/  mov_eax_moffs64 ; 
 int /*<<< orphan*/  mov_eax_moffs64_32 ; 
 int /*<<< orphan*/  mov_rax_moffs64 ; 
 int /*<<< orphan*/  mov_rax_moffs64_32 ; 
 int /*<<< orphan*/  pcmpistri ; 
 int /*<<< orphan*/  ptu_run (struct ptunit_suite,int /*<<< orphan*/ ) ; 
 struct ptunit_suite ptunit_mk_suite (int,char**) ; 
 int ptunit_report (struct ptunit_suite*) ; 
 int /*<<< orphan*/  ptwrite_m32 ; 
 int /*<<< orphan*/  ptwrite_m64 ; 
 int /*<<< orphan*/  ptwrite_r32 ; 
 int /*<<< orphan*/  ptwrite_r64 ; 
 int /*<<< orphan*/  push ; 
 int /*<<< orphan*/  rdtsc ; 
 int /*<<< orphan*/  ret_ca ; 
 int /*<<< orphan*/  syscall ; 
 int /*<<< orphan*/  sysenter ; 
 int /*<<< orphan*/  sysexit ; 
 int /*<<< orphan*/  sysret ; 
 int /*<<< orphan*/  vmcall ; 
 int /*<<< orphan*/  vmlaunch ; 
 int /*<<< orphan*/  vmovdqa ; 
 int /*<<< orphan*/  vmptrld ; 
 int /*<<< orphan*/  vmresume ; 
 int /*<<< orphan*/  vpandn ; 
 int /*<<< orphan*/  vpshufb ; 

int main(int argc, char **argv)
{
	struct ptunit_suite suite;

	suite = ptunit_mk_suite(argc, argv);

	ptu_run(suite, push);
	ptu_run(suite, jmp_rel);
	ptu_run(suite, long_nop);
	ptu_run(suite, mov_al_64);
	ptu_run(suite, mov_al_32);
	ptu_run(suite, mov_al_32_em64);
	ptu_run(suite, mov_al_32_em16);
	ptu_run(suite, mov_al_16_em32);
	ptu_run(suite, mov_al_16);
	ptu_run(suite, rdtsc);
	ptu_run(suite, pcmpistri);
	ptu_run(suite, vmovdqa);
	ptu_run(suite, vpandn);
	ptu_run(suite, syscall);
	ptu_run(suite, sysret);
	ptu_run(suite, sysenter);
	ptu_run(suite, sysexit);
	ptu_run(suite, int3);
	ptu_run(suite, intn);
	ptu_run(suite, iret);
	ptu_run(suite, call_9a_cd);
	ptu_run(suite, call_9a_cp);
	ptu_run(suite, call_ff_3);
	ptu_run(suite, jmp_ff_5);
	ptu_run(suite, jmp_ea_cd);
	ptu_run(suite, jmp_ea_cp);
	ptu_run(suite, ret_ca);
	ptu_run(suite, vmlaunch);
	ptu_run(suite, vmresume);
	ptu_run(suite, vmcall);
	ptu_run(suite, vmptrld);
	ptu_run(suite, jrcxz);
	ptu_run(suite, mov_eax_moffs64);
	ptu_run(suite, mov_eax_moffs64_32);
	ptu_run(suite, mov_rax_moffs64);
	ptu_run(suite, mov_rax_moffs64_32);
	ptu_run(suite, mov_ax_moffs64);
	ptu_run(suite, mov_ax_moffs64_32);
	ptu_run(suite, mov_eax_moffs32);
	ptu_run(suite, mov_ax_moffs32);
	ptu_run(suite, mov_ax_moffs16);
	ptu_run(suite, les);
	ptu_run(suite, les_disp16);
	ptu_run(suite, les_disp32);
	ptu_run(suite, les_ind_disp8);
	ptu_run(suite, les_ind_disp16);
	ptu_run(suite, les_ind_disp32);
	ptu_run(suite, lds);
	ptu_run(suite, lds_disp16);
	ptu_run(suite, lds_disp32);
	ptu_run(suite, lds_ind_disp8);
	ptu_run(suite, lds_ind_disp16);
	ptu_run(suite, lds_ind_disp32);
	ptu_run(suite, vpshufb);
	ptu_run(suite, bound);
	ptu_run(suite, evex_cutoff);
	ptu_run(suite, ptwrite_r32);
	ptu_run(suite, ptwrite_m32);
	ptu_run(suite, ptwrite_r64);
	ptu_run(suite, ptwrite_m64);

	return ptunit_report(&suite);
}