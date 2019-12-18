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
struct spu_state {int dummy; } ;
struct spu {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  check_ppu_mb_stat (struct spu_state*,struct spu*) ; 
 int /*<<< orphan*/  check_ppuint_mb_stat (struct spu_state*,struct spu*) ; 
 int /*<<< orphan*/  clear_interrupts (struct spu_state*,struct spu*) ; 
 int /*<<< orphan*/  enable_user_access (struct spu_state*,struct spu*) ; 
 int /*<<< orphan*/  issue_mfc_tlbie (struct spu_state*,struct spu*) ; 
 int /*<<< orphan*/  reenable_interrupts (struct spu_state*,struct spu*) ; 
 int /*<<< orphan*/  reset_switch_active (struct spu_state*,struct spu*) ; 
 int /*<<< orphan*/  restore_ch_part1 (struct spu_state*,struct spu*) ; 
 int /*<<< orphan*/  restore_ch_part2 (struct spu_state*,struct spu*) ; 
 int /*<<< orphan*/  restore_decr_wrapped (struct spu_state*,struct spu*) ; 
 int /*<<< orphan*/  restore_ls_16kb (struct spu_state*,struct spu*) ; 
 int /*<<< orphan*/  restore_mfc_cntl (struct spu_state*,struct spu*) ; 
 int /*<<< orphan*/  restore_mfc_csr_ato (struct spu_state*,struct spu*) ; 
 int /*<<< orphan*/  restore_mfc_csr_cmd (struct spu_state*,struct spu*) ; 
 int /*<<< orphan*/  restore_mfc_csr_tsq (struct spu_state*,struct spu*) ; 
 int /*<<< orphan*/  restore_mfc_queues (struct spu_state*,struct spu*) ; 
 int /*<<< orphan*/  restore_mfc_sr1 (struct spu_state*,struct spu*) ; 
 int /*<<< orphan*/  restore_mfc_tclass_id (struct spu_state*,struct spu*) ; 
 int /*<<< orphan*/  restore_other_spu_access (struct spu_state*,struct spu*) ; 
 int /*<<< orphan*/  restore_pm_trace (struct spu_state*,struct spu*) ; 
 int /*<<< orphan*/  restore_ppu_querymask (struct spu_state*,struct spu*) ; 
 int /*<<< orphan*/  restore_ppu_querytype (struct spu_state*,struct spu*) ; 
 int /*<<< orphan*/  restore_spu_cfg (struct spu_state*,struct spu*) ; 
 int /*<<< orphan*/  restore_spu_lslr (struct spu_state*,struct spu*) ; 
 int /*<<< orphan*/  restore_spu_mb (struct spu_state*,struct spu*) ; 
 int /*<<< orphan*/  restore_spu_npc (struct spu_state*,struct spu*) ; 
 int /*<<< orphan*/  restore_spu_privcntl (struct spu_state*,struct spu*) ; 
 int /*<<< orphan*/  restore_spu_runcntl (struct spu_state*,struct spu*) ; 
 int /*<<< orphan*/  restore_status_part1 (struct spu_state*,struct spu*) ; 
 int /*<<< orphan*/  restore_status_part2 (struct spu_state*,struct spu*) ; 
 int /*<<< orphan*/  set_int_route (struct spu_state*,struct spu*) ; 
 int /*<<< orphan*/  set_llr_event (struct spu_state*,struct spu*) ; 
 int /*<<< orphan*/  spu_invalidate_slbs (struct spu*) ; 
 int /*<<< orphan*/  suspend_mfc (struct spu_state*,struct spu*) ; 
 int /*<<< orphan*/  wait_suspend_mfc_complete (struct spu_state*,struct spu*) ; 
 int /*<<< orphan*/  wait_tag_complete (struct spu_state*,struct spu*) ; 

__attribute__((used)) static void restore_csa(struct spu_state *next, struct spu *spu)
{
	/*
	 * Combine steps 41-76 of SPU context restore sequence, which
	 * restore regions of the privileged & problem state areas.
	 */

	restore_spu_privcntl(next, spu);	/* Step 41. */
	restore_status_part1(next, spu);	/* Step 42. */
	restore_status_part2(next, spu);	/* Step 43. */
	restore_ls_16kb(next, spu);	        /* Step 44. */
	wait_tag_complete(next, spu);	        /* Step 45. */
	suspend_mfc(next, spu);	                /* Step 46. */
	wait_suspend_mfc_complete(next, spu);	/* Step 47. */
	issue_mfc_tlbie(next, spu);	        /* Step 48. */
	clear_interrupts(next, spu);	        /* Step 49. */
	restore_mfc_queues(next, spu);	        /* Step 50. */
	restore_ppu_querymask(next, spu);	/* Step 51. */
	restore_ppu_querytype(next, spu);	/* Step 52. */
	restore_mfc_csr_tsq(next, spu);	        /* Step 53. */
	restore_mfc_csr_cmd(next, spu);	        /* Step 54. */
	restore_mfc_csr_ato(next, spu);	        /* Step 55. */
	restore_mfc_tclass_id(next, spu);	/* Step 56. */
	set_llr_event(next, spu);	        /* Step 57. */
	restore_decr_wrapped(next, spu);	/* Step 58. */
	restore_ch_part1(next, spu);	        /* Step 59. */
	restore_ch_part2(next, spu);	        /* Step 60. */
	restore_spu_lslr(next, spu);	        /* Step 61. */
	restore_spu_cfg(next, spu);	        /* Step 62. */
	restore_pm_trace(next, spu);	        /* Step 63. */
	restore_spu_npc(next, spu);	        /* Step 64. */
	restore_spu_mb(next, spu);	        /* Step 65. */
	check_ppu_mb_stat(next, spu);	        /* Step 66. */
	check_ppuint_mb_stat(next, spu);	/* Step 67. */
	spu_invalidate_slbs(spu);		/* Modified Step 68. */
	restore_mfc_sr1(next, spu);	        /* Step 69. */
	set_int_route(next, spu);		/* NEW      */
	restore_other_spu_access(next, spu);	/* Step 70. */
	restore_spu_runcntl(next, spu);	        /* Step 71. */
	restore_mfc_cntl(next, spu);	        /* Step 72. */
	enable_user_access(next, spu);	        /* Step 73. */
	reset_switch_active(next, spu);	        /* Step 74. */
	reenable_interrupts(next, spu);	        /* Step 75. */
}