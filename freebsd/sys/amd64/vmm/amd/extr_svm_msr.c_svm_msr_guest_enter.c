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
svm_msr_guest_enter(struct svm_softc *sc, int vcpu)
{
	/*
	 * Save host MSRs (if any) and restore guest MSRs (if any).
	 */
}