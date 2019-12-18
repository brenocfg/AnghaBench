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
 int /*<<< orphan*/  COUNTER_ARRAY_FREE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RACK_OPTS_SIZE ; 
 int /*<<< orphan*/  TCP_MSS_ACCT_SIZE ; 
 int /*<<< orphan*/  counter_u64_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rack_alloc_limited_conns ; 
 int /*<<< orphan*/  rack_badfr ; 
 int /*<<< orphan*/  rack_badfr_bytes ; 
 int /*<<< orphan*/  rack_collapsed_win ; 
 int /*<<< orphan*/  rack_enter_tlp_calc ; 
 int /*<<< orphan*/  rack_find_high ; 
 int /*<<< orphan*/  rack_input_idle_reduces ; 
 int /*<<< orphan*/  rack_opts_arry ; 
 int /*<<< orphan*/  rack_out_size ; 
 int /*<<< orphan*/  rack_paced_segments ; 
 int /*<<< orphan*/  rack_progress_drops ; 
 int /*<<< orphan*/  rack_reorder_seen ; 
 int /*<<< orphan*/  rack_rtm_prr_newdata ; 
 int /*<<< orphan*/  rack_rtm_prr_retran ; 
 int /*<<< orphan*/  rack_sack_proc_all ; 
 int /*<<< orphan*/  rack_sack_proc_restart ; 
 int /*<<< orphan*/  rack_sack_proc_short ; 
 int /*<<< orphan*/  rack_saw_enetunreach ; 
 int /*<<< orphan*/  rack_saw_enobuf ; 
 int /*<<< orphan*/  rack_split_limited ; 
 int /*<<< orphan*/  rack_timestamp_mismatch ; 
 int /*<<< orphan*/  rack_tlp_does_nada ; 
 int /*<<< orphan*/  rack_tlp_newdata ; 
 int /*<<< orphan*/  rack_tlp_retran ; 
 int /*<<< orphan*/  rack_tlp_retran_bytes ; 
 int /*<<< orphan*/  rack_tlp_retran_fail ; 
 int /*<<< orphan*/  rack_tlp_tot ; 
 int /*<<< orphan*/  rack_to_alloc ; 
 int /*<<< orphan*/  rack_to_alloc_emerg ; 
 int /*<<< orphan*/  rack_to_alloc_hard ; 
 int /*<<< orphan*/  rack_to_alloc_limited ; 
 int /*<<< orphan*/  rack_to_arm_rack ; 
 int /*<<< orphan*/  rack_to_arm_tlp ; 
 int /*<<< orphan*/  rack_to_tot ; 
 int /*<<< orphan*/  rack_unpaced_segments ; 
 int /*<<< orphan*/  rack_used_tlpmethod ; 
 int /*<<< orphan*/  rack_used_tlpmethod2 ; 

__attribute__((used)) static void
rack_counter_destroy(void)
{
	counter_u64_free(rack_badfr);
	counter_u64_free(rack_badfr_bytes);
	counter_u64_free(rack_rtm_prr_retran);
	counter_u64_free(rack_rtm_prr_newdata);
	counter_u64_free(rack_timestamp_mismatch);
	counter_u64_free(rack_reorder_seen);
	counter_u64_free(rack_tlp_tot);
	counter_u64_free(rack_tlp_newdata);
	counter_u64_free(rack_tlp_retran);
	counter_u64_free(rack_tlp_retran_bytes);
	counter_u64_free(rack_tlp_retran_fail);
	counter_u64_free(rack_to_tot);
	counter_u64_free(rack_to_arm_rack);
	counter_u64_free(rack_to_arm_tlp);
	counter_u64_free(rack_paced_segments);
	counter_u64_free(rack_unpaced_segments);
	counter_u64_free(rack_saw_enobuf);
	counter_u64_free(rack_saw_enetunreach);
	counter_u64_free(rack_to_alloc_hard);
	counter_u64_free(rack_to_alloc_emerg);
	counter_u64_free(rack_sack_proc_all);
	counter_u64_free(rack_sack_proc_short);
	counter_u64_free(rack_sack_proc_restart);
	counter_u64_free(rack_to_alloc);
	counter_u64_free(rack_to_alloc_limited);
	counter_u64_free(rack_alloc_limited_conns);
	counter_u64_free(rack_split_limited);
	counter_u64_free(rack_find_high);
	counter_u64_free(rack_enter_tlp_calc);
	counter_u64_free(rack_used_tlpmethod);
	counter_u64_free(rack_used_tlpmethod2);
	counter_u64_free(rack_progress_drops);
	counter_u64_free(rack_input_idle_reduces);
	counter_u64_free(rack_collapsed_win);
	counter_u64_free(rack_tlp_does_nada);
	COUNTER_ARRAY_FREE(rack_out_size, TCP_MSS_ACCT_SIZE);
	COUNTER_ARRAY_FREE(rack_opts_arry, RACK_OPTS_SIZE);
}