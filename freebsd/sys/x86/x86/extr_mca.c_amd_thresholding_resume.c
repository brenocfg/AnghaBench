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
struct amd_et_state {int cur_threshold; scalar_t__ last_intr; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 size_t PCPU_GET (int /*<<< orphan*/ ) ; 
 struct amd_et_state** amd_et_state ; 
 int /*<<< orphan*/  amd_thresholding_start (struct amd_et_state*,int) ; 
 int /*<<< orphan*/  cmci_mask ; 
 int /*<<< orphan*/  cpuid ; 
 int mca_banks ; 

__attribute__((used)) static void
amd_thresholding_resume(int i)
{
	struct amd_et_state *cc;

	KASSERT(i < mca_banks, ("CPU %d has more MC banks", PCPU_GET(cpuid)));

	/* Ignore banks not monitored by this CPU. */
	if (!(PCPU_GET(cmci_mask) & 1 << i))
		return;

	cc = &amd_et_state[PCPU_GET(cpuid)][i];
	cc->last_intr = 0;
	cc->cur_threshold = 1;
	amd_thresholding_start(cc, i);
}