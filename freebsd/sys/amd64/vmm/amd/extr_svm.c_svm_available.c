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

/* Variables and functions */
 int AMDID2_SVM ; 
 int /*<<< orphan*/  MSR_VM_CR ; 
 int VM_CR_SVMDIS ; 
 int amd_feature2 ; 
 int /*<<< orphan*/  printf (char*) ; 
 int rdmsr (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
svm_available(void)
{
	uint64_t msr;

	/* Section 15.4 Enabling SVM from APM2. */
	if ((amd_feature2 & AMDID2_SVM) == 0) {
		printf("SVM: not available.\n");
		return (0);
	}

	msr = rdmsr(MSR_VM_CR);
	if ((msr & VM_CR_SVMDIS) != 0) {
		printf("SVM: disabled by BIOS.\n");
		return (0);
	}

	return (1);
}