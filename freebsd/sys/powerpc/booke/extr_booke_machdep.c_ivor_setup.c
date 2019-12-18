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

/* Variables and functions */
 uintptr_t EPCR_ICM ; 
#define  FSL_E500mc 132 
#define  FSL_E500v1 131 
#define  FSL_E500v2 130 
#define  FSL_E5500 129 
#define  FSL_E6500 128 
 int /*<<< orphan*/  SET_TRAP (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SPR_EPCR ; 
 int /*<<< orphan*/  SPR_IVOR0 ; 
 int /*<<< orphan*/  SPR_IVOR1 ; 
 int /*<<< orphan*/  SPR_IVOR10 ; 
 int /*<<< orphan*/  SPR_IVOR11 ; 
 int /*<<< orphan*/  SPR_IVOR12 ; 
 int /*<<< orphan*/  SPR_IVOR13 ; 
 int /*<<< orphan*/  SPR_IVOR14 ; 
 int /*<<< orphan*/  SPR_IVOR15 ; 
 int /*<<< orphan*/  SPR_IVOR2 ; 
 int /*<<< orphan*/  SPR_IVOR3 ; 
 int /*<<< orphan*/  SPR_IVOR32 ; 
 int /*<<< orphan*/  SPR_IVOR33 ; 
 int /*<<< orphan*/  SPR_IVOR34 ; 
 int /*<<< orphan*/  SPR_IVOR35 ; 
 int /*<<< orphan*/  SPR_IVOR4 ; 
 int /*<<< orphan*/  SPR_IVOR5 ; 
 int /*<<< orphan*/  SPR_IVOR6 ; 
 int /*<<< orphan*/  SPR_IVOR7 ; 
 int /*<<< orphan*/  SPR_IVOR8 ; 
 int /*<<< orphan*/  SPR_IVPR ; 
 int /*<<< orphan*/  int_alignment ; 
 int /*<<< orphan*/  int_critical_input ; 
 int /*<<< orphan*/  int_data_storage ; 
 int /*<<< orphan*/  int_data_tlb_error ; 
 int /*<<< orphan*/  int_debug ; 
 int /*<<< orphan*/  int_debug_ed ; 
 int /*<<< orphan*/  int_decrementer ; 
 int /*<<< orphan*/  int_external_input ; 
 int /*<<< orphan*/  int_fixed_interval_timer ; 
 int /*<<< orphan*/  int_fpu ; 
 int /*<<< orphan*/  int_inst_tlb_error ; 
 int /*<<< orphan*/  int_instr_storage ; 
 int /*<<< orphan*/  int_machine_check ; 
 int /*<<< orphan*/  int_performance_counter ; 
 int /*<<< orphan*/  int_program ; 
 int /*<<< orphan*/  int_spe_fpdata ; 
 int /*<<< orphan*/  int_spe_fpround ; 
 int /*<<< orphan*/  int_syscall ; 
 int /*<<< orphan*/  int_vec ; 
 int /*<<< orphan*/  int_vecast ; 
 int /*<<< orphan*/  int_watchdog ; 
 int /*<<< orphan*/  interrupt_vector_base ; 
 int mfpvr () ; 
 uintptr_t mfspr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtspr (int /*<<< orphan*/ ,uintptr_t) ; 

void
ivor_setup(void)
{

	mtspr(SPR_IVPR, ((uintptr_t)&interrupt_vector_base) & ~0xffffUL);

	SET_TRAP(SPR_IVOR0, int_critical_input);
	SET_TRAP(SPR_IVOR1, int_machine_check);
	SET_TRAP(SPR_IVOR2, int_data_storage);
	SET_TRAP(SPR_IVOR3, int_instr_storage);
	SET_TRAP(SPR_IVOR4, int_external_input);
	SET_TRAP(SPR_IVOR5, int_alignment);
	SET_TRAP(SPR_IVOR6, int_program);
	SET_TRAP(SPR_IVOR8, int_syscall);
	SET_TRAP(SPR_IVOR10, int_decrementer);
	SET_TRAP(SPR_IVOR11, int_fixed_interval_timer);
	SET_TRAP(SPR_IVOR12, int_watchdog);
	SET_TRAP(SPR_IVOR13, int_data_tlb_error);
	SET_TRAP(SPR_IVOR14, int_inst_tlb_error);
	SET_TRAP(SPR_IVOR15, int_debug);
#ifdef HWPMC_HOOKS
	SET_TRAP(SPR_IVOR35, int_performance_counter);
#endif
	switch ((mfpvr() >> 16) & 0xffff) {
	case FSL_E6500:
		SET_TRAP(SPR_IVOR32, int_vec);
		SET_TRAP(SPR_IVOR33, int_vecast);
		/* FALLTHROUGH */
	case FSL_E500mc:
	case FSL_E5500:
		SET_TRAP(SPR_IVOR7, int_fpu);
		SET_TRAP(SPR_IVOR15, int_debug_ed);
		break;
	case FSL_E500v1:
	case FSL_E500v2:
		SET_TRAP(SPR_IVOR32, int_vec);
#ifdef __SPE__
		SET_TRAP(SPR_IVOR33, int_spe_fpdata);
		SET_TRAP(SPR_IVOR34, int_spe_fpround);
#endif
		break;
	}

#ifdef __powerpc64__
	/* Set 64-bit interrupt mode. */
	mtspr(SPR_EPCR, mfspr(SPR_EPCR) | EPCR_ICM);
#endif
}