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
typedef  int uint64_t ;
struct mca_record {int mr_status; } ;
struct cmc_state {int /*<<< orphan*/  last_intr; int /*<<< orphan*/  max_threshold; } ;
typedef  enum scan_mode { ____Placeholder_scan_mode } scan_mode ;

/* Variables and functions */
 int CMCI ; 
 int MC_CTL2_THRESHOLD ; 
 int MC_STATUS_COR_COUNT ; 
 int /*<<< orphan*/  MSR_MC_CTL2 (int) ; 
 size_t PCPU_GET (int /*<<< orphan*/ ) ; 
 struct cmc_state** cmc_state ; 
 int /*<<< orphan*/  cpuid ; 
 int rdmsr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  time_uptime ; 
 int update_threshold (int,int,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wrmsr (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
cmci_update(enum scan_mode mode, int bank, int valid, struct mca_record *rec)
{
	struct cmc_state *cc;
	uint64_t ctl;
	int cur_threshold, new_threshold;
	int count;

	/* Fetch the current limit for this bank. */
	cc = &cmc_state[PCPU_GET(cpuid)][bank];
	ctl = rdmsr(MSR_MC_CTL2(bank));
	count = (rec->mr_status & MC_STATUS_COR_COUNT) >> 38;
	cur_threshold = ctl & MC_CTL2_THRESHOLD;

	new_threshold = update_threshold(mode, valid, cc->last_intr, count,
	    cur_threshold, cc->max_threshold);

	if (mode == CMCI && valid)
		cc->last_intr = time_uptime;
	if (new_threshold != cur_threshold) {
		ctl &= ~MC_CTL2_THRESHOLD;
		ctl |= new_threshold;
		wrmsr(MSR_MC_CTL2(bank), ctl);
	}
}