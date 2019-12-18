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
struct svm_softc {int dummy; } ;

/* Variables and functions */

void
svm_msr_guest_init(struct svm_softc *sc, int vcpu)
{
	/*
	 * All the MSRs accessible to the guest are either saved/restored by
	 * hardware on every #VMEXIT/VMRUN (e.g., G_PAT) or are saved/restored
	 * by VMSAVE/VMLOAD (e.g., MSR_GSBASE).
	 *
	 * There are no guest MSRs that are saved/restored "by hand" so nothing
	 * more to do here.
	 */
	return;
}