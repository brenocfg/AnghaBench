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
 int VMCB_NPF_INFO1_GPA ; 
 int VMCB_NPF_INFO1_GPT ; 
 int VMCB_NPF_INFO1_ID ; 

__attribute__((used)) static bool
svm_npf_emul_fault(uint64_t exitinfo1)
{
	
	if (exitinfo1 & VMCB_NPF_INFO1_ID) {
		return (false);
	}

	if (exitinfo1 & VMCB_NPF_INFO1_GPT) {
		return (false);
	}

	if ((exitinfo1 & VMCB_NPF_INFO1_GPA) == 0) {
		return (false);
	}

	return (true);	
}