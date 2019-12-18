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
struct cmc_state {int max_threshold; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int MC_CTL2_CMCI_EN ; 
 int MC_CTL2_THRESHOLD ; 
 int /*<<< orphan*/  MSR_MC_CTL2 (int) ; 
 int PCPU_GET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PCPU_SET (int /*<<< orphan*/ ,int) ; 
 struct cmc_state** cmc_state ; 
 int /*<<< orphan*/  cmci_mask ; 
 int /*<<< orphan*/  cpuid ; 
 int mca_banks ; 
 int rdmsr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wrmsr (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
cmci_monitor(int i)
{
	struct cmc_state *cc;
	uint64_t ctl;

	KASSERT(i < mca_banks, ("CPU %d has more MC banks", PCPU_GET(cpuid)));

	ctl = rdmsr(MSR_MC_CTL2(i));
	if (ctl & MC_CTL2_CMCI_EN)
		/* Already monitored by another CPU. */
		return;

	/* Set the threshold to one event for now. */
	ctl &= ~MC_CTL2_THRESHOLD;
	ctl |= MC_CTL2_CMCI_EN | 1;
	wrmsr(MSR_MC_CTL2(i), ctl);
	ctl = rdmsr(MSR_MC_CTL2(i));
	if (!(ctl & MC_CTL2_CMCI_EN))
		/* This bank does not support CMCI. */
		return;

	cc = &cmc_state[PCPU_GET(cpuid)][i];

	/* Determine maximum threshold. */
	ctl &= ~MC_CTL2_THRESHOLD;
	ctl |= 0x7fff;
	wrmsr(MSR_MC_CTL2(i), ctl);
	ctl = rdmsr(MSR_MC_CTL2(i));
	cc->max_threshold = ctl & MC_CTL2_THRESHOLD;

	/* Start off with a threshold of 1. */
	ctl &= ~MC_CTL2_THRESHOLD;
	ctl |= 1;
	wrmsr(MSR_MC_CTL2(i), ctl);

	/* Mark this bank as monitored. */
	PCPU_SET(cmci_mask, PCPU_GET(cmci_mask) | 1 << i);
}