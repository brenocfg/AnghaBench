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
struct amrr_node {int /*<<< orphan*/  amn_success_threshold; scalar_t__ amn_recovery; scalar_t__ amn_success; scalar_t__ amn_tx_failure_cnt; scalar_t__ amn_tx_try3_cnt; scalar_t__ amn_tx_try2_cnt; scalar_t__ amn_tx_try1_cnt; scalar_t__ amn_tx_try0_cnt; } ;

/* Variables and functions */
 int /*<<< orphan*/  ath_rate_min_success_threshold ; 

__attribute__((used)) static void 
node_reset(struct amrr_node *amn)
{
	amn->amn_tx_try0_cnt = 0;
	amn->amn_tx_try1_cnt = 0;
	amn->amn_tx_try2_cnt = 0;
	amn->amn_tx_try3_cnt = 0;
	amn->amn_tx_failure_cnt = 0;
  	amn->amn_success = 0;
  	amn->amn_recovery = 0;
  	amn->amn_success_threshold = ath_rate_min_success_threshold;
}