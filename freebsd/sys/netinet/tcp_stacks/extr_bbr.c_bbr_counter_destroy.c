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
 int /*<<< orphan*/  BBR_MAX_STAT ; 
 int /*<<< orphan*/  BBR_OPTS_SIZE ; 
 int /*<<< orphan*/  BBR_STAT_SIZE ; 
 int /*<<< orphan*/  COUNTER_ARRAY_FREE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TCP_MSS_ACCT_SIZE ; 
 int /*<<< orphan*/  bbr_flows_nohdwr_pacing ; 
 int /*<<< orphan*/  bbr_flows_whdwr_pacing ; 
 int /*<<< orphan*/  bbr_opts_arry ; 
 int /*<<< orphan*/  bbr_out_size ; 
 int /*<<< orphan*/  bbr_stat_arry ; 
 int /*<<< orphan*/  bbr_state_lost ; 
 int /*<<< orphan*/  bbr_state_resend ; 
 int /*<<< orphan*/  bbr_state_time ; 
 int /*<<< orphan*/  counter_u64_free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bbr_counter_destroy(void)
{
	COUNTER_ARRAY_FREE(bbr_stat_arry, BBR_STAT_SIZE);
	COUNTER_ARRAY_FREE(bbr_opts_arry, BBR_OPTS_SIZE);
	COUNTER_ARRAY_FREE(bbr_out_size, TCP_MSS_ACCT_SIZE);
	COUNTER_ARRAY_FREE(bbr_state_lost, BBR_MAX_STAT);
	COUNTER_ARRAY_FREE(bbr_state_time, BBR_MAX_STAT);
	COUNTER_ARRAY_FREE(bbr_state_resend, BBR_MAX_STAT);
	counter_u64_free(bbr_flows_whdwr_pacing);
	counter_u64_free(bbr_flows_nohdwr_pacing);

}